#include "uiGameManager.h"
#include "../data.h"
#include "../gameTime/gameTime.h"

using namespace std;

constexpr const char MODEL_PATH[] =
 "data/graphic/ui/powerUpGauge.png" ;			//ロードするファイル名

constexpr VECTOR GET_COIN_POS[PLAYER_NUM] =
{
	{115.0f,60.0f,0.0f},
	{WINDOW_SIZE_X - 115.0f,60.0f,0.0f},
	{115.0f,120.0f,0.0f},
	{WINDOW_SIZE_X - 115.0f,120.0f,0.0f},

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
	m_time.Exit();
	m_eventText.Exit();

	for (int playerStautusPanel_i = 0; playerStautusPanel_i < PLAYER_NUM; playerStautusPanel_i++)
	{
		m_playerStautusPanel[playerStautusPanel_i].Exit();
	}
}

