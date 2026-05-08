#include "ranking.h"
#include <algorithm>

CRanking* CRanking::m_instanse = nullptr;

CRanking::CRanking()
{
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		tagRankingData rankData;
		rankData.m_coin = 0;
		rankData.m_name = PLAYER_NONE;
		m_rankingData.push_back(rankData);
	}
	Init();
}

CRanking::~CRanking()
{

}

//初期化
void CRanking::Init()
{
	for (int ranking_i = 0;  ranking_i < m_rankingData.size();  ranking_i++)
	{
		m_rankingData[ranking_i].m_coin = 0;
		m_rankingData[ranking_i].m_name = PLAYER_NONE;
	}
}

//ステップ
void CRanking::Step(CPlayerManager* _playerManager)
{

	//最高コイン保存用
	int high = 0;

	//プレイヤーからコインなどの情報を取得する
	for (int player_i = 0; player_i < _playerManager->GetPlayerNum(); player_i++)
	{
		CPlayer* player = _playerManager->GetPlayer(player_i);

		m_rankingData[player_i].m_coin = player->GetMoney();
		m_rankingData[player_i].m_name = player->GetPlayerName();
	}

	//コインの数で順位を決める
	std::sort(m_rankingData.begin(),m_rankingData.end(),
		[](const tagRankingData& _a, const tagRankingData& _b)
		{
			return _a.m_coin > _b.m_coin;
		});
}

//プレイヤーの獲得したコインを取得
int CRanking::GetPlayerGetCoin(tagPlayerName _playerName)
{
	for (int ranking_i = 0; ranking_i < m_rankingData.size(); ranking_i++)
	{
		if (m_rankingData[ranking_i].m_name == _playerName)
			return m_rankingData[ranking_i].m_coin;
	}

	return 0;
}

//プレイヤーの順位を取得
int CRanking::GetPlayerRank(tagPlayerName _playerName)
{
	for (int ranking_i = 0; ranking_i < PLAYER_NUM; ranking_i++)
	{
		if (m_rankingData[ranking_i].m_name == _playerName)
			return ranking_i;
	}

	return -1;
}

