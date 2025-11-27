#include "playerManager.h"
#include "../../lib/input/controllerManager.h"


enum tagModelName					//モデル一覧
{
	MODEL_PLAYER1,					//プレイヤー１のモデル
	MODEL_PLAYER2,					//プレイヤー２のモデル

	MODEL_NUM,						//モデルの数
};

static const char* MODEL_PATH[PLAYER_NUM] =
{ "data/model/player/playerTest6-1.mv1" ,
  "data/model/player/playerTest6-2.mv1" ,};			//ロードするファイル名

static const char FRAME_PATH[] =
{ "data/model/map/TestMap6Frame.mv1" };			//ロードするファイル名

static const float FIGHT_LEN = 40.0f;		//戦う距離

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
void CPlayerManager::Init(CAttackManager* _attackManager)
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

		switch (player_i)
		{
		case PLAYER_1:
			name = PLAYER_1;
			break;
		case PLAYER_2:
			name = PLAYER_2;
			break;
		}

		m_player[player_i]->Init(_attackManager,name, padName);

	}
	
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
		case 0:
			start = MV1GetFramePosition(frameHndl, 1);
			break;
		case 1:
			start = MV1GetFramePosition(frameHndl, 3);
			break;
		}

		start.y += 50;
		m_player[i]->Load(m_modelHndl[i]);
		m_player[i]->SetPos(start);
	}
}

//------------------------
//	毎フレームする処理
//------------------------
void CPlayerManager::Step(float _rot)
{
	for (int i = 0; i < m_player.size(); i++)
	{
		m_player[i]->Step(_rot);

	}

	//計算用のプレイヤーの座標
	VECTOR player1Pos = m_player[PLAYER_1]->GetPos();
	VECTOR player2Pos = m_player[PLAYER_2]->GetPos();

	//プレイヤー同士の距離
	VECTOR vLen = VSub(player1Pos, player2Pos);
	float fLen = VSize(vLen);

	//戦いの距離になったら互いの方向を向く
	if (fLen <= FIGHT_LEN)
	{
		if (!m_player[PLAYER_1]->GetIsDodgeroll())
		{
			float rotY1 = atan2f(player1Pos.x - player2Pos.x, player1Pos.z - player2Pos.z);

			m_player[PLAYER_1]->SetRot(0.0f, rotY1);
		}

		if (!m_player[PLAYER_2]->GetIsDodgeroll())
		{
			float rotY2 = atan2f(player2Pos.x - player1Pos.x, player2Pos.z - player1Pos.z);

			m_player[PLAYER_2]->SetRot(0.0f, rotY2);
		}
	}

	//投げる状態のときに相手の方向を向く
	if (m_player[PLAYER_1]->GetState() == ITEM_THROW_IN)
	{
		float rotY1 = atan2f(player1Pos.x - player2Pos.x, player1Pos.z - player2Pos.z);

		m_player[PLAYER_1]->SetRot(0.0f, rotY1);
	}

	if (m_player[PLAYER_2]->GetState() == ITEM_THROW_IN)
	{
		float rotY2 = atan2f(player2Pos.x - player1Pos.x, player2Pos.z - player1Pos.z);

		m_player[PLAYER_2]->SetRot(0.0f, rotY2);
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

