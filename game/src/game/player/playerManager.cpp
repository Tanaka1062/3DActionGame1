#include "playerManager.h"


static const char* MODEL_PATH[PAD_NUM] =
{ "data/model/player/playerTest4-1.mv1" ,
  "data/model/player/playerTest4-2.mv1" ,};			//ロードするファイル名

static const char FRAME_PATH[] =
{ "data/model/map/TestMap4FramePos.mv1" };			//ロードするファイル名

static const int PLAYER_NUM = 1;					//プレイヤーの数

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
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		delete m_player[i];
	}

}

//------------------------
//		  初期化
//------------------------
void CPlayerManager::Init(CAttackManager* _attackManager)
{

	for (int i = 0; i < PAD_NUM; i++)
	{
		m_modelHndl[i] = -1;

		m_player.push_back(new CPlayer);

		//コントローラーの名前を取得
		tagPadName padName = CControllerManager::GetName(i);

		m_player[i]->Init(_attackManager,padName);
	}

	
}

//------------------------
//	オブジェクトのロード
//------------------------
void CPlayerManager::Load()
{

	//モデルのロード
	for (int i = 0; i < PAD_NUM; i++)
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
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_player[i]->Exit();

	}

}

