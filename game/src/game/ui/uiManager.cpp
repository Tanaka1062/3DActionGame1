#include "uiManager.h"
#include "hpber/hpbar.h"
#include "../data.h"

static const VECTOR GET_COIN_POS[PLAYER_NUM] =
{
	{}
};

//UIの名前
enum tagUiName
{
	UI_PLAYER1_HPBAR,			//プレイヤー１のHPバー
	UI_PLAYER2_HPBAR,			//プレイヤー2のHPバー

	UI_NUM,						//UIの数
};

//コンストラクタ・デストラクタ
CUiManager::CUiManager()
{
	Init();
}

CUiManager::~CUiManager()
{
	Exit();
}

void CUiManager::Init(CPlayerManager* _playerManager, 
	CPowerCoinManager* _powerCoinManager)
{
	m_hpbarManager.Init(_playerManager);

	for (int getCoinUi_i = 0; getCoinUi_i < PLAYER_NUM; getCoinUi_i++)
	{
		m_getCoinUi[getCoinUi_i].Init();
	}
}

//ロード
void CUiManager::Load()
{
	m_hpbarManager.Load();
	for (int i = 0; i < m_ui.size(); i++)
	{
		
	}
}

//毎フレームする処理
void CUiManager::Step()
{
	m_hpbarManager.Step();
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i]->Step();
	}
}

//描写
void CUiManager::Draw()
{
	m_hpbarManager.Draw();
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i]->Draw();
	}
}

//破棄
void CUiManager::Exit()
{
	m_hpbarManager.Exit();
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i]->Exit();

		delete m_ui[i];
	}
	m_ui.clear();
}

