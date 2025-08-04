#include "shotManager.h"

//定義関連===========================
static const char PLSHOT_MODEL_PATH[] ="data/model/shot/shot.x";	//プレイヤーの弾のモデルパス
static const int PL_SHOT_NUM = 50;									//プレイヤーの弾の数
//===================================

//---------------------------
//		コンストラクタ
//---------------------------
CShotManager::CShotManager()
{
	Init();
}

//---------------------------
//		初期化
//---------------------------
void CShotManager::Init()
{
	if (m_playerShot.size() != PL_SHOT_NUM)
	{
		for (int i = 0; i < PL_SHOT_NUM; i++)
		{
			CShot shot;
			shot.Init();
			m_playerShot.push_back(shot);
		}
	}
	else
	{
		for (int i = 0; i < m_playerShot.size(); i++)
		{
			m_playerShot[i].Init();
		}
	}

}

//---------------------------
//		ロード
//---------------------------
void CShotManager::Load()
{
	//オリジナルのモデルをロード
	int hndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	for (int i = 0; i < m_playerShot.size(); i++)
	{
		m_playerShot[i].DuplicateModel(hndl);
	}

	//複製が終わったら即破棄
	MV1DeleteModel(hndl);
}

//---------------------------
//	毎フレームする処理
//---------------------------
void CShotManager::Step()
{
	for (int i = 0; i < m_playerShot.size(); i++)
	{
		m_playerShot[i].Step();
	}

}

//---------------------------
//		描写
//---------------------------
void CShotManager::Draw()
{
	for (int i = 0; i < m_playerShot.size(); i++)
	{
		m_playerShot[i].Draw();
	}

}

//---------------------------
//		終了処理
//---------------------------
void CShotManager::Exit()
{
	for (int i = 0; i < m_playerShot.size(); i++)
	{
		m_playerShot[i].Exit();
	}
}


//---------------------------
//		座標更新
//---------------------------
void CShotManager::Update()
{
	for (int i = 0; i < m_playerShot.size(); i++)
	{
		m_playerShot[i].Update();
	}

}

//---------------------------
//		弾をリクエスト
//---------------------------
void CShotManager::RequestPlayerShot(
	const VECTOR& _pos, const VECTOR& _speed)
{
	for (int i = 0; i < m_playerShot.size(); i++)
	{
		//弾を発射
		if (m_playerShot[i].Request(_pos, _speed))
		{
			//弾を発射したら終了
			break;
		}
	}
}
