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

constexpr float TARGET_LEN = 70.0f;				//ターゲットと認識するまでの長さ
constexpr float TARGET_MAX_DISTANCE = 20.0f;	//どれくらい法線から離せるか

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
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		//ターゲットの座標アドレス保存用
		VECTOR* targetPos = nullptr;

		//プレイヤーとターゲットの最小距離保存用
		float minLen = -1.0f;

		//プレイヤーの座標
		VECTOR playerPos = m_player[player_i]->GetPos();

		//プレイヤーが向いてる方向の長さベクトル
		VECTOR vecLen = playerPos;
		//プレイヤーの向いている方向
		float playerRotY = m_player[player_i]->GetRot().y;

		vecLen.x += sinf(playerRotY) * TARGET_LEN;
		vecLen.z += cosf(playerRotY) * TARGET_LEN;

		//一番近いプレイヤーの座標を求める
		for (int target_i = 0; target_i < m_player.size(); target_i++)
		{
			//同じプレイヤーはスキップする
			if (player_i == target_i)continue;

			//プレイヤーとターゲットの内積
			float dot1 = CMyMath::VecDot(m_player[target_i]->GetPos(), playerPos);
			//プレイヤーの向いている方向ベクトルとターゲットの内積
			float dot2 = CMyMath::VecDot(m_player[target_i]->GetPos(), vecLen);

			//ターゲットが前方にいるかを判断し後方なら処理をしない
			if (dot1 < 0 && dot2 < 0)continue;

			//外積を出すために必要なベクトル１
			VECTOR vec1 = VSub(vecLen, playerPos);
			//外積を出すために必要なベクトル２
			VECTOR vec2 = VSub(m_player[target_i]->GetPos(),playerPos);

			//外積を求める
			VECTOR cross = ZERO;
			cross.x = vec1.y * vec2.z - vec1.z * vec2.y;
			cross.y = vec1.z * vec2.x - vec1.x * vec2.z;
			cross.z = vec1.x * vec2.y - vec1.y * vec2.x;

			//外積から平行四辺形の面積を計算
			float area = cross.x * cross.x + cross.y * cross.y + cross.z * cross.z;

			area = sqrtf(area);

			//平行四辺形の底辺を求める
			float baseLength = vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z;

			baseLength = sqrtf(baseLength);

			//プレイヤーの向いてる方向ベクトルからターゲットまでの距離
			float len = area / baseLength;

			//今の距離より近かったらターゲットの座標を変更
			if ((minLen >= len && TARGET_MAX_DISTANCE >= len) || minLen == -1.0f)
			{
				minLen = len;

				targetPos = m_player[target_i]->GetPosPoint();
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
