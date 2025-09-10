#include "shotManager.h"

static const char MODEL_PATH[] =
{ "data/model/shot/shotTest.mv1" };				//ロードするファイル名

//------------------------
//	  コンストラクタ
//------------------------
CShotManager::CShotManager()
{

}

//------------------------
//	  デストラクタ
//------------------------
CShotManager::~CShotManager()
{
	Exit();
}


//------------------------
//	毎フレームする処理
//------------------------
void CShotManager::Step()
{
	for (auto ite = m_shot.begin(); ite != m_shot.end();)
	{
		//毎フレームする処理
		(*ite)->Step();

		//生存してない弾を消す
		if ((*ite)->GetActive() == false)
		{
			ite = m_shot.erase(ite);
		}
		else
		{
			++ite;
		}

	}
}

//------------------------
//		 数値の更新
//------------------------
void CShotManager::Update()
{
	for (auto ite = m_shot.begin(); ite != m_shot.end();++ite)
	{
		//更新処理
		(*ite)->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CShotManager::Draw()
{
	for (auto ite = m_shot.begin(); ite != m_shot.end();++ite)
	{
		//描写処理
		(*ite)->Draw();
	}
}


//------------------------
//		 終了処理
//------------------------
void CShotManager::Exit()
{
	for (auto ite = m_shot.begin(); ite != m_shot.end();)
	{
		//終了処理
		(*ite)->Exit();

		//終了処理が終わった弾を消す
		ite = m_shot.erase(ite);
	}
}

//------------------------
//	ショットの呼び出し
//------------------------
void CShotManager::Request(VECTOR _pos, VECTOR _rot, float _speed, int _atk, int _lostTime)
{
	//弾のベースクラスにデータを入力
	CShotBase shot;
	shot.Init();
	shot.Load(MODEL_PATH);
	shot.Request(_pos,_rot,_speed,_atk,_lostTime);
	
	//弾を追加
	m_shot.push_back(&shot);
}

