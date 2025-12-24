#include "playerManager.h"
#include "../../lib/input/controllerManager.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"

using namespace std;

enum tagModelName					//モデル一覧
{
	MODEL_PLAYER1,					//プレイヤー1のモデル
	MODEL_PLAYER2,					//プレイヤー2のモデル
	MODEL_PLAYER3,					//プレイヤー3のモデル
	MODEL_PLAYER4,					//プレイヤー4のモデル

	MODEL_NUM,						//モデルの数
};

constexpr float TARGET_LEN = 200.0f;				//ターゲットと認識するまでの長さ
constexpr float TARGET_MAX_DISTANCE = 40.0f;	//どれくらい法線から離せるか

static const char* MODEL_PATH[PLAYER_NUM] =
{ "data/model/player/playerTest7-1.mv1" ,
  "data/model/player/playerTest7-2.mv1" ,
  "data/model/player/playerTest7-3.mv1" ,
  "data/model/player/playerTest7-4.mv1" ,};			//ロードするファイル名

static const char FRAME_PATH[] =
"data/model/map/TestMap6Frame.mv1";			//ロードするファイル名


//------------------------
//	  コンストラクタ
//------------------------
CPlayerManager::CPlayerManager()
{
	Init();
}

//------------------------
//	  デストラクタ
//------------------------
CPlayerManager::~CPlayerManager()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		delete m_player[player_i];

		m_player[player_i]->Exit();

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

	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		//コントローラーの名前を取得
		tagPadName padName = CControllerManager::GetName(player_i);

		//プレイヤーがいなかったら増やす
		if (m_player.size() < PLAYER_NUM)
		{
			m_player.push_back(new CPlayer);
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

		m_player[player_i]->Init(name, padName);

	}
	
	//スポーン座標を全て消す
	m_spawnPos.clear();
}

//------------------------
//	オブジェクトのロード
//------------------------
void CPlayerManager::Load()
{

	//モデルのロード
	for (int i = 0; i < MODEL_NUM; i++)
	{
		if (m_modelHndl[i] == -1)
		{
			m_modelHndl[i] = MV1LoadModel(MODEL_PATH[i]);
		}
	}

	//マップのフレームのハンドルをロード
	int frameHndl = MV1LoadModel(FRAME_PATH);

	for (int i = 0; i < m_player.size(); i++)
	{
		//プレイヤーのスポーン位置をロード
		VECTOR start = { 0.0f,0.0f,0.0f };

		//スポーン位置をセット
		switch (i)
		{
		case PLAYER_1:
			start = MV1GetFramePosition(frameHndl, 1);
			break;
		case PLAYER_2:
			start = MV1GetFramePosition(frameHndl, 3);
			break;
		case PLAYER_3:
			start = MV1GetFramePosition(frameHndl, 33);
			break;
		case PLAYER_4:
			start = MV1GetFramePosition(frameHndl, 31);
			break;
		}

		start.y += 50;
		m_player[i]->Load(m_modelHndl[i]);
		m_player[i]->SetPos(start);
		m_spawnPos.push_back(start);
	}
}

//------------------------
//	毎フレームする処理
//------------------------
void CPlayerManager::Step(CAttackManager* _attackManager, CShotManager* _shotManager, float _rot)
{
	test = 0;

	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{

		//ターゲットの座標アドレス保存用
		VECTOR* targetPos = nullptr;

		//プレイヤーとターゲットの最小距離保存用
		float minLen = TARGET_MAX_DISTANCE;

		//プレイヤーの座標
		VECTOR playerPos = m_player[player_i]->GetPos();

		//プレイヤーの向いている方向
		float playerRotY = m_player[player_i]->GetRot().y;

		VECTOR forwardVec;

		forwardVec.x = cosf(playerRotY);
		forwardVec.z = sinf(playerRotY);
		forwardVec.y = 0.0f;

		VECTOR endPos = VAdd(playerPos, VScale(forwardVec, TARGET_LEN));

		if (player_i != PLAYER_2)
		{
			m_player[player_i]->Step(_rot, targetPos, _attackManager, _shotManager);
			continue;
		}

		//一番近いプレイヤーの座標を求める
		for (int target_i = 0; target_i < m_player.size(); target_i++)
		{
			//同じプレイヤーはスキップする
			if (player_i == target_i)continue;

			float fArea;		// 面積を保存
			float fBottom;		// 底辺を保存
			float fLength;		// キャラクター1と線分の最短距離を保存
			VECTOR v1, v2, vCross;

			v1 = VSub(m_player[target_i]->GetPos(),forwardVec);

			v2 = VSub(playerPos,forwardVec);

			VECTOR cross = VCross(v1, v2);

			fArea = cross.x * cross.x + cross.y * cross.y + cross.z * cross.z;
			fArea = sqrt(fArea);

			v1 = VSub(playerPos,forwardVec);
			fBottom = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
			fBottom = sqrtf(fBottom);

			fLength = fArea / fBottom;

			v1 = VSub(m_player[target_i]->GetPos(), playerPos);
			v2 = VSub(forwardVec, playerPos);

			float fDot = VDot(v1,v2);

			if (fDot < 0.0f)
			{
				VECTOR v3 = VSub(m_player[target_i]->GetPos(),playerPos );
				fLength = sqrtf((v3.x * v3.x) + (v3.y * v3.y) + (v3.z * v3.z));
			}

			v1 = VSub(m_player[target_i]->GetPos(),forwardVec);
			v2 = VSub(m_player[target_i]->GetPos(), forwardVec);
			fDot = VDot(v1, v2);

			if (fDot < 0.0f)
			{
				VECTOR V3 = VSub(m_player[target_i]->GetPos(),forwardVec);
				fLength = sqrt((V3.x * V3.x) + (V3.y * V3.y) + (V3.z * V3.z));
			}

			if (fLength < minLen)
			{
				minLen = fLength;

				targetPos = m_player[target_i]->GetPosPoint();
			}
	
			if (target_i == PLAYER_1)
			{
				test = minLen;
			}
		}

		//プレイヤーが死んでいたら復活させる
		if (m_player[player_i]->GetActive() == false)
		{
			m_player[player_i]->Respawn(m_spawnPos[player_i]);
		}

		m_player[player_i]->Step(_rot,targetPos,_attackManager,_shotManager);
	}


}

//------------------------
//		 数値の更新
//------------------------
void CPlayerManager::Update()
{
	for (int i = 0; i < m_player.size(); i++)
	{
		m_player[i]->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CPlayerManager::Draw()
{
	for (int i = 0; i < m_player.size(); i++)
	{
		m_player[i]->Draw();
	}


	DrawFormatString(300, 200, GetColor(255, 0, 0), "%f", test);

}

//------------------------
//		  終了処理
//------------------------
void CPlayerManager::Exit()
{
	for (int i = 0; i < m_player.size(); i++)
	{

	}
	m_player.clear();

	for (int i = 0; i < m_modelHndl.size(); i++)
	{
		m_modelHndl[i] = -1;
	}

	m_modelHndl.clear();
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
