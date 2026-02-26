#include "winner.h"

CWinner* CWinner::m_instanse = nullptr;

CWinner::CWinner()
{
	Init();
}

CWinner::~CWinner()
{

}

//初期化
void CWinner::Init()
{
	m_winnerPlayer = PLAYER_NONE;

	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_playerGetCoin[player_i] = 0;
	}
}

//ステップ
void CWinner::Step(CPlayerManager* _playerManager)
{
	int high = 0;

	for (int player_i = 0; player_i < _playerManager->GetPlayerNum(); player_i++)
	{
		CPlayer* player = _playerManager->GetPlayer(player_i);

		m_playerGetCoin[player_i] = player->GetMoney();

		if (high <= m_playerGetCoin[player_i])
		{
			high = m_playerGetCoin[player_i];
			m_winnerPlayer = player->GetPlayerName();
		}
	}
}

