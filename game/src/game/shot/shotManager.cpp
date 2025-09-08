#include "shotManager.h"

static const char MODEL_PATH[] =
{ "data/model/shot/shotTest.mv1" };				//ロードするファイル名

//------------------------
//	  コンストラクタ
//------------------------
CShotManager::CShotManager()
{
	Init();
}

//------------------------
//	  デストラクタ
//------------------------
CShotManager::~CShotManager()
{
	int shotNum = m_shot.size();
	for (int i = 0; i < shotNum; i++)
	{
		delete m_shot[i];
	}

}

//------------------------
//		  初期化
//------------------------
void CShotManager::Init()
{

}

//------------------------
//	オブジェクトのロード
//------------------------
void CShotManager::Load()
{
	for (int i = 0; i < m_shot.size(); i++)
	{
		m_shot[i]->Load(MODEL_PATH);
	}
}

//------------------------
//	毎フレームする処理
//------------------------
void CShotManager::Step()
{
	for (int i = 0; i < m_shot.size(); i++)
	{
		m_shot[i]->Step();
	}
}

//------------------------
//		 数値の更新
//------------------------
void CShotManager::Update()
{
	for (int i = 0; i < m_shot.size(); i++)
	{
		m_shot[i]->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CShotManager::Draw()
{
	for (int i = 0; i < m_shot.size(); i++)
	{
		m_shot[i]->Draw();
	}
}


//------------------------
//		 終了処理
//------------------------
void CShotManager::Exit()
{
	for (int i = 0; i < m_shot.size(); i++)
	{
		m_shot[i]->Exit();

	}
	
}

//------------------------
//	ショットの呼び出し
//------------------------
void CShotManager::Request(VECTOR _pos, VECTOR _rot, VECTOR _speed, int _atk, int _lostTime)
{
	//弾のベースクラスにデータを入力
	CShotBase* shot;
	shot->Request(_pos,_rot,_speed,_atk,_lostTime);
	for (int i = 0; i < m_shot.size(); i++)
	{
		if (m_shot[i]->GetActive() == false)
		{
			m_shot[i] = new shot;
		}
	}
}

