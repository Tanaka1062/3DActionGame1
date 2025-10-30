#include "uiManager.h"

//コンストラクタ・デストラクタ
CUiManager::CUiManager()
{
	Init();
}

CUiManager::~CUiManager()
{
	Exit();
}

void CUiManager::Init()
{

}

//ロード
void CUiManager::Load()
{
	for (int i = 0; i < m_ui.size(); i++)
	{
		
	}
}

//毎フレームする処理
void CUiManager::Step()
{
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i]->Step();
	}
}

//描写
void CUiManager::Draw()
{
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i]->Draw();
	}
}

//破棄
void CUiManager::Exit()
{
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i]->Exit();

		delete m_ui[i];
	}
	m_ui.clear();
}

