#include "playerManager.h"
#include "../../lib/input/controllerManager.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include "cpuPlayer/cpuPlayer.h"
#include "../camera/cameraManager.h"
#include "../common.h"
#include "../../lib/collision/collision.h"

using namespace std;

enum tagModelName					//モデル一覧
{
	MODEL_PLAYER1,					//プレイヤー1のモデル
	MODEL_PLAYER2,					//プレイヤー2のモデル
	MODEL_PLAYER3,					//プレイヤー3のモデル
	MODEL_PLAYER4,					//プレイヤー4のモデル

	MODEL_NUM,						//モデルの数
};

constexpr float TARGET_LEN = -200.0f;			//ターゲットと認識するまでの長さ
constexpr float TARGET_MAX_DISTANCE = 40.0f;	//どれくらい法線から離せるか

constexpr int MAP_FRAME_NUM = 15;				//マップのフレーム番号
constexpr float DIE_RADIUS = 240.0f;			//画面外判定の半径

static const char* MODEL_PATH[PLAYER_NUM] =
{ "data/model/player/playerTest7-1.mv1" ,
  "data/model/player/playerTest7-2.mv1" ,
  "data/model/player/playerTest7-3.mv1" ,
  "data/model/player/playerTest7-4.mv1" ,};			//ロードするファイル名


//------------------------
//	  コンストラクタ
//------------------------
CPlayerManager::CPlayerManager()
{
}

//------------------------
//	  デストラクタ
//------------------------
CPlayerManager::~CPlayerManager()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{

		m_player[player_i]->Exit();

		delete m_player[player_i];

	}

	for (int cpuFOV_i = 0; cpuFOV_i < m_cpuFOV.size(); cpuFOV_i++)
	{
		m_cpuFOV[cpuFOV_i]->Exit();

		delete m_cpuFOV[cpuFOV_i];
	}

}

//------------------------
//		  初期化
//------------------------
void CPlayerManager::Init()
{
	if (m_modelHndl.size() < MODEL_NUM)
	{
		for (int modelHndl_i = 0; modelHndl_i < MODEL_NUM; modelHndl_i++)
		{
			m_modelHndl.push_back(-1);
		}
	}

	for (int cpuFOV_i = 0; cpuFOV_i < PLAYER_NUM; cpuFOV_i++)
	{
		m_cpuFOV.push_back(new CCpuPlayerFOV);
	}

	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		//コントローラーの名前を取得
		tagPadName padName = CControllerManager::GetName(player_i);

		CPlayer* player = nullptr;

		//コントローラーが接続されているかでCPUかを判断
		if (CControllerManager::IsConnection(padName) == true)
		{
			player = new CPlayer;
		}
		else
		{
			CCpuPlayer* cpuPlayer = new CCpuPlayer;
			cpuPlayer->SetFOV(m_cpuFOV[player_i]);

			player = cpuPlayer;
		}

		tagPlayerName name = PLAYER_NONE;

		VECTOR* pointerPos = nullptr;

		switch (player_i)
		{
		case PLAYER_1:
			name = PLAYER_1;
			break;
		case PLAYER_2:
			name = PLAYER_2;
			break;
		case PLAYER_3:
			name = PLAYER_3;
			break;
		case PLAYER_4:
			name = PLAYER_4;
			break;

		}

		player->Init(name,padName);

		m_player.push_back(player);
	}

	//リスポーン場所作成
	for (int map_i = 0; map_i < MAP_CENTER_NUM; map_i++)
	{
		m_spawnPos.push_back(vector<VECTOR>());
	}

	//王冠の初期化
	m_crown.Init();
}

//------------------------
//	オブジェクトのロード
//------------------------
void CPlayerManager::Load()
{

	//モデルのロード
	for (int model_i = 0; model_i < MODEL_NUM; model_i++)
	{
		if (m_modelHndl[model_i] == -1)
		{
			m_modelHndl[model_i] = MV1LoadModel(MODEL_PATH[model_i]);
		}
	}

	//マップのフレームのハンドルをロード
	int mapFrameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_GRASSLAND]);

	int frameNum = MAP_FRAME_NUM;
	//マップのリスポーン位置を取得して設定
	for (int map_i = 0; map_i < m_spawnPos.size(); map_i++)
	{
		for (int spawn_i = 0; spawn_i < PLAYER_NUM; spawn_i++)
		{
			//プレイヤーのスポーン位置をロード
			VECTOR pos = { 0.0f,0.0f,0.0f };

			//フレームから座標を取得
			pos = MV1GetFramePosition(mapFrameHndl, frameNum);

			//フレームを次に進める
			frameNum += 2;

			//上空に移動させる
			pos.y += 50;

			//スポーン位置を生成して設定
			m_spawnPos[map_i].push_back(pos);
		}
	}

	///マップのフレームを削除
	if (mapFrameHndl != -1)
	{
		MV1DeleteModel(mapFrameHndl);
	}

	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Load(m_modelHndl[player_i]);
		m_player[player_i]->SetPos(m_spawnPos[MAP_ID_CENTER1][player_i]);
	}

	//王冠のモデルロード
	m_crown.Load();
}

//------------------------
//	毎フレームする処理
//------------------------
void CPlayerManager::Step(CAttackManager* _attackManager, CShotManager* _shotManager, float _rot,tagMapCenterId _mapId)
{
	int topPlayerCoinCount = 0;	//現在の一番コインを持っている量
	int topPlayerNum = -1;		//一番のプレイヤーの番号
	bool isTieAtTop = false;	//同率一位がいるかどうかフラグ

	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		//プレイヤーがカメラの外に行くと死ぬ処理---------------

		if (CCollision::CheckHitSphereToSphere(m_player[player_i]->GetCenter(), m_player[player_i]->GetRad(),
			CCameraManager::GetFocusPos(), DIE_RADIUS) == false)
		{
			m_player[player_i]->SetActive(false);
		}

		//-----------------------------------------------------

		//ターゲットの座標アドレス保存用
		VECTOR* targetPos = nullptr;

		//プレイヤーとターゲットの最小距離保存用
		float minLen = TARGET_MAX_DISTANCE;

		//プレイヤーの座標
		VECTOR playerPos = m_player[player_i]->GetPos();

		//プレイヤーの向いている方向
		float playerRotY = m_player[player_i]->GetRot().y;

		//プレイヤーの向いている方向ベクトル
		VECTOR forwardVec;

		forwardVec.x = sinf(playerRotY);
		forwardVec.z = cosf(playerRotY);
		forwardVec.y = 0.0f;

		//方向ベクトルを加算して終点を求める
		VECTOR endPos = VAdd(playerPos, VScale(forwardVec, TARGET_LEN));

		//一番近いプレイヤーの座標を求める
		for (int target_i = 0; target_i < m_player.size(); target_i++)
		{
			//同じプレイヤーはスキップする
			if (player_i == target_i)continue;

			float fArea;		// 面積を保存
			float fBottom;		// 底辺を保存
			float fLength;		// ターゲットとプレイヤーの目線の最短距離を保存
			VECTOR v1, v2;		//ベクトル保存用

			//終点からターゲットまでの距離を求める
			v1 = VSub(m_player[target_i]->GetPos(), endPos);
			v1.y = 0.0f;

			//終点からプレイヤーまでの距離を求める
			v2 = VSub(playerPos, endPos);
			v2.y = 0.0f;

			//上の二つの外積を求める
			VECTOR cross = VCross(v1, v2);

			//外積から平行四辺形の面積を求める
			fArea = cross.x * cross.x + cross.y * cross.y + cross.z * cross.z;
			fArea = sqrt(fArea);

			//終点からプレイヤーまでの距離を求める
			v1 = VSub(playerPos, endPos);
			v1.y = 0.0f;

			//v1を使って平行四辺形の底辺を求める
			fBottom = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
			fBottom = sqrtf(fBottom);

			//面積から底辺を割って離れている距離を求める
			fLength = fArea / fBottom;

			//プレイヤーからターゲットまでの距離を求める
			v1 = VSub(m_player[target_i]->GetPos(), playerPos);
			v1.y = 0.0f;

			//プレイヤーからプレイヤーの視点の終点までの距離を求める
			v2 = VSub(endPos, playerPos);
			v2.y = 0.0f;

			//v1とv2の内積を求める
			float fDot = VDot(v1,v2);

			//内積が0以下なら範囲に入っているので最短距離を求めて保存
			if (fDot < 0.0f)
			{
				VECTOR v3 = VSub(m_player[target_i]->GetPos(),playerPos );
				v3.y = 0.0f;
				fLength = sqrtf((v3.x * v3.x) + (v3.y * v3.y) + (v3.z * v3.z));
			}

			//プレイヤーの視点の終点からターゲットまでの距離を求める
			v1 = VSub(m_player[target_i]->GetPos(), endPos);
			v1.y = 0.0f;

			//プレイヤーの視点の終点からターゲットまでの距離を求める
			v2 = VSub(m_player[target_i]->GetPos(), endPos);
			v2.y = 0.0f;

			//v1とv2の内積を求める
			fDot = VDot(v1, v2);

			//内積が0以下なら範囲に入っているので最短距離を求めて保存
			if (fDot < 0.0f)
			{
				VECTOR V3 = VSub(m_player[target_i]->GetPos(), endPos);
				V3.y = 0.0f;
				fLength = sqrt((V3.x * V3.x) + (V3.y * V3.y) + (V3.z * V3.z));
			}

			//最短距離が今の最小距離以下なら長さを保存してターゲットを保存
			if (fLength < minLen)
			{
				minLen = fLength;

				targetPos = m_player[target_i]->GetPosPoint();
			}
		}

		//プレイヤーが死んでいたら復活させる
		if (m_player[player_i]->GetActive() == false)
		{
			if (CCollision::CheckHitSphereToSphere(m_spawnPos[_mapId][player_i], m_player[player_i]->GetRad(),
				CCameraManager::GetFocusPos(), DIE_RADIUS) == true)
			{
				m_player[player_i]->Respawn(m_spawnPos[_mapId][player_i]);
			}
		}

		m_player[player_i]->Step(_rot,targetPos,_attackManager,_shotManager);

		//現在のコイン取得数が一番多い人を求める-------------------------------------------

		//お金が一番か調べる
		if (m_player[player_i]->GetMoney() >= topPlayerCoinCount)
		{
			//一位と一緒ならフラグをtrueにする
			if (m_player[player_i]->GetMoney() == topPlayerCoinCount)
			{
				isTieAtTop = true;
			}
			else
			{
				topPlayerCoinCount = m_player[player_i]->GetMoney();
				topPlayerNum = player_i;
			}
		}

		//---------------------------------------------------------------------------------
	}

	//一位に王冠を表示する-----------------------------------------------------------------
	if (isTieAtTop == false && topPlayerNum != -1)
	{
		m_crown.SetActive(true);
		m_crown.Step(m_player[topPlayerNum]->GetPos(), m_player[topPlayerNum]->GetRad(), _rot);
	}
	else
	{
		m_crown.SetActive(false);
	}
	//-------------------------------------------------------------------------------------
}

//------------------------
//		 数値の更新
//------------------------
void CPlayerManager::Update()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Update();
	}
	m_crown.Update();
}

//------------------------
//	オブジェクトの描写
//------------------------
void CPlayerManager::Draw()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		if (m_player[player_i]->GetActive() == false)continue;
		m_player[player_i]->Draw();
	}

	m_crown.Draw();

#ifdef DEBUG
	DrawSphere3D(CCameraManager::GetFocusPos(), DIE_RADIUS, 16, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
#endif // DEBUG
}

//------------------------
//		  終了処理
//------------------------
void CPlayerManager::Exit()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{

		m_player[player_i]->Exit();

		delete m_player[player_i];

	}
	m_player.clear();

	for (int model_i = 0; model_i < m_modelHndl.size(); model_i++)
	{
		if (m_modelHndl[model_i] != -1)
		{
			MV1DeleteModel(m_modelHndl[model_i]);
			m_modelHndl[model_i] = -1;
		}
	}
	m_modelHndl.clear();

	for (int cpuFOV_i = 0; cpuFOV_i < m_cpuFOV.size(); cpuFOV_i++)
	{
		m_cpuFOV[cpuFOV_i]->Exit();

		delete m_cpuFOV[cpuFOV_i];
	}
	m_cpuFOV.clear();

	//スポーン座標を全て消す
	m_spawnPos.clear();

	m_crown.Exit();
}

//------------------------
//ゲームが終わったかを取得
//------------------------
bool CPlayerManager::GetIsEnd()
{
	//死んだプレイヤーの数
	int playerDieNum = 0;
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		//死んでいるプレイヤーを確認
		if (m_player[player_i]->GetState() == DIE)
		{
			playerDieNum++;
		}
	}

	//一人以外死んでいたらゲームを終わる
	if (playerDieNum == PLAYER_NUM - 1)
	{
		return true;
	}

	return false;
}
