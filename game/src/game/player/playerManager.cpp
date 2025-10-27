#include "playerManager.h"


static const char* MODEL_PATH[PLAYER_MODEL_ID_NUM] =
{ "data/model/player/playerTest4-2.mv1" ,
  "data/model/player/playerTest4-2.mv1" ,};			//ロードするファイル名

static const char ROOT_PATH[] =
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

	for (int i = 0; i < PLAYER_MODEL_ID_NUM; i++)
	{
		m_modelHndl[i] = -1;
	}

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_player.push_back(new CPlayer);

		m_player[i]->Init(_attackManager);
	}


}

//------------------------
//	オブジェクトのロード
//------------------------
void CPlayerManager::Load()
{
	for (int i = 0; i < PLAYER_MODEL_ID_NUM; i++)
	{
		if (m_modelHndl[i] == -1)
		{
			m_modelHndl[i] = MV1LoadModel(MODEL_PATH[i]);
		}
	}


	for (int i = 0; i < m_player.size(); i++)
	{
		m_player[i]->Load(m_modelHndl[i]);
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

