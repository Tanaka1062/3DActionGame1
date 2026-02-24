#include "uiGameManager.h"
#include "hpber/hpbar.h"
#include "../data.h"
#include "../gameTime/gameTime.h"

using namespace std;

static const char MODEL_PATH[] =
 "data/graphic/ui/powerUpGauge.png" ;			//ロードするファイル名

constexpr VECTOR GET_COIN_POS[PLAYER_NUM] =
{
	{115.0f,60.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X - 115),60.0f,0.0f},
	{115.0f,120.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X - 115),120.0f,0.0f},

};

constexpr VECTOR GET_POWER_GOUGE_POS[PLAYER_NUM] =
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
CUiGameManager::CUiGameManager()
{
	Init();
}

CUiGameManager::~CUiGameManager()
{
	Exit();
}

void CUiGameManager::Init(CPlayerManager* _playerManager,
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

	m_time.Init();
	m_eventText.Init();

	for (int playerStautusPanel_i = 0; playerStautusPanel_i < PLAYER_NUM; playerStautusPanel_i++)
	{
		m_playerStautusPanel[playerStautusPanel_i].Init();
	}
}

//ロード
void CUiGameManager::Load()
{
	m_hpbarManager.Load();

	for (int i = 0; i < m_ui.size(); i++)
	{
		
	}

	for (int powerUpGuge_i = 0; powerUpGuge_i < PLAYER_NUM; powerUpGuge_i++)
	{
		m_powerUpGouge[powerUpGuge_i].Load(MODEL_PATH);
	}

	m_time.Load();
	m_eventText.Load();

	for (int playerStautusPanel_i = 0; playerStautusPanel_i < PLAYER_NUM; playerStautusPanel_i++)
	{
		m_playerStautusPanel[playerStautusPanel_i].Load(static_cast<tagPlayerName>(playerStautusPanel_i));
	}
}

//毎フレームする処理
void CUiGameManager::Step(CEventManager::tagEventName _nowEvent, CPlayerManager& _playerManager)
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

	CGameTime* gameTime = CGameTime::GetInstance();

	m_time.Step(gameTime->GetEndTime() - gameTime->GetTime());
	m_eventText.Step(_nowEvent);

	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_playerStautusPanel[player_i].Step(_playerManager.GetPlayer(player_i));
	}
}

//描写
void CUiGameManager::Draw()
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
	m_time.Draw();
	m_eventText.Draw();
	
	for (int playerStautusPanel_i = 0; playerStautusPanel_i < PLAYER_NUM; playerStautusPanel_i++)
	{
		m_playerStautusPanel[playerStautusPanel_i].Draw();
	}
}

//破棄
void CUiGameManager::Exit()
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

	m_time.Exit();
	m_eventText.Exit();

	for (int playerStautusPanel_i = 0; playerStautusPanel_i < PLAYER_NUM; playerStautusPanel_i++)
	{
		m_playerStautusPanel[playerStautusPanel_i].Exit();
	}
}

