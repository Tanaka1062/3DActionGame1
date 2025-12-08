#include "uiManager.h"
#include "hpber/hpbar.h"
#include "../data.h"

static const char MODEL_PATH[] =
{ "data/graphic/ui/powerUpGauge.png" };			//ロードするファイル名

static const VECTOR GET_COIN_POS[PLAYER_NUM] =
{
	{115.0f,60.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X - 115),60.0f,0.0f},
	{115.0f,120.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X - 115),120.0f,0.0f},

};

static const VECTOR GET_POWER_GOUGE_POS[PLAYER_NUM] =
{
	{360.0f,60.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X - 360),60.0f,0.0f},
	{360.0f,120.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X - 360),120.0f,0.0f}
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
	CItemManager* _itemManager)
{
	m_hpbarManager.Init(_playerManager);


	for (int powerUpGuge_i = 0; powerUpGuge_i < PLAYER_NUM; powerUpGuge_i++)
	{
		VECTOR pos = ZERO;

		pos = GET_POWER_GOUGE_POS[powerUpGuge_i];

		m_powerUpGouge[powerUpGuge_i].Init(pos);

		if (_playerManager != nullptr)
		{
			m_powerUpGouge[powerUpGuge_i].SetPlayer(_playerManager->GetPlayer(powerUpGuge_i));
		}
	}
}

//ロード
void CUiManager::Load()
{
	m_hpbarManager.Load();

	for (int i = 0; i < m_ui.size(); i++)
	{
		
	}

	for (int powerUpGuge_i = 0; powerUpGuge_i < PLAYER_NUM; powerUpGuge_i++)
	{
		m_powerUpGouge[powerUpGuge_i].Load(MODEL_PATH);
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

	for (int powerUpGuge_i = 0; powerUpGuge_i < PLAYER_NUM; powerUpGuge_i++)
	{
		m_powerUpGouge[powerUpGuge_i].Step();
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

	for (int powerUpGuge_i = 0; powerUpGuge_i < PLAYER_NUM; powerUpGuge_i++)
	{
		m_powerUpGouge[powerUpGuge_i].Draw();
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

	for (int powerUpGuge_i = 0; powerUpGuge_i < PLAYER_NUM; powerUpGuge_i++)
	{
		m_powerUpGouge[powerUpGuge_i].Exit();
	}
}

