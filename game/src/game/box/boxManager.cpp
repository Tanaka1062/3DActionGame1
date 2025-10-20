#include "boxManager.h"

static const int BOX_MAX = 1;

//---------------------------
//		コンストラクタ
//---------------------------
CBoxManager::CBoxManager()
{
}

//---------------------------
//		 デストラクタ
//---------------------------
CBoxManager::~CBoxManager()
{
	Exit();
}

//---------------------------
//		   初期化
//---------------------------
void CBoxManager::Init()
{
	CBox* box = new CBox;

	box->Init();
	box->SetPos(VGet(0.0f,0.0f,0.0f));

	m_box.push_back(box);
}

//---------------------------
//		 モデルロード
//---------------------------
void CBoxManager::Load()
{
	for (auto ite = m_box.begin(); ite != m_box.end(); ite++)
	{
		(*ite)->Load();
	}
}

//---------------------------
//	   毎フレームする処理
//---------------------------
void CBoxManager::Step()
{
	for (auto ite = m_box.begin(); ite != m_box.end(); ite++)
	{
		(*ite)->Update();
	}

}

//---------------------------
//		  モデル描写
//---------------------------
void CBoxManager::Draw()
{
	for (auto ite = m_box.begin(); ite != m_box.end(); ite++)
	{
		(*ite)->Draw();
	}

}

//---------------------------
//		   終了処理
//---------------------------
void CBoxManager::Exit()
{
	for (auto ite = m_box.begin(); ite != m_box.end(); ite++)
	{
		(*ite)->Exit();
	}

}

