#include "winner.h"

CWinner* CWinner::m_instanse = nullptr;

CWinner::CWinner()
{
	m_winnerPlayer = PLAYER_NONE;
}

CWinner::~CWinner()
{

}

//初期化
void CWinner::Init()
{
	m_winnerPlayer = PLAYER_NONE;
}

//ステップ
void CWinner::Step(CPlayerManager* _playerManager)
{
	int high = 0;

	for (int player_i = 0; player_i < _playerManager->GetPlayerNum(); player_i++)
	{
		CPlayer* player = _playerManager->GetPlayer(player_i);

		if (high <= player->GetMoney())
		{
			high = player->GetMoney();
			m_winnerPlayer = player->GetPlayerName();
		}
	}
}
