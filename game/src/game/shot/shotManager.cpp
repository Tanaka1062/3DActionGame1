#include "shotManager.h"

constexpr const char MODEL_PATH[] =
 "data/model/shot/shotTest.mv1" ;				//ロードするファイル名

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
	Exit();
}

//------------------------
//		 初期化
//------------------------
void CShotManager::Init()
{
	m_hndl = -1;
}

//------------------------
//	   モデルロード
//------------------------
void CShotManager::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = MV1LoadModel(MODEL_PATH);
	}
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
			//終了処理
			(*ite)->Exit();

			delete (*ite);

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

		delete (*ite);

		//終了処理が終わった弾を消す
		ite = m_shot.erase(ite);
	}
}

//------------------------
//	ショットの呼び出し
//------------------------
void CShotManager::Request(VECTOR _pos, VECTOR _rot, float _rad, float _speed, int _atk, int _lostTime,
	tagPlayerName _name,int _effectHndl, VECTOR* _targetPos)
{
	//弾のベースクラスにデータを入力
	CShotBase* shot = new CShotBase;
	shot->Init();
	shot->Load(m_hndl);
	shot->Request(_pos,_rot,_rad,_speed,_atk,_lostTime,_name,_effectHndl,_targetPos);
	
	//弾を追加
	m_shot.push_back(shot);
}

//------------------------
//	 弾のアドレスを取得
//------------------------
CShotBase* CShotManager::GetShot(int _num)
{
	//引数より弾の数が少なければnullを返す
	if (_num > m_shot.size())return nullptr;
	//弾の数をカウントする変数
	int count = 0;
	for (auto ite = m_shot.begin(); ite != m_shot.end(); ++ite)
	{
		//引数の数字と同じならアドレスを返す
		if (count == _num)
		{
			return *ite;
		}
		count++;

	}
	return nullptr;
}

