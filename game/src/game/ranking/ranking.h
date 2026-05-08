#pragma once
#include "../player/playerData.h"
#include "../player/playerManager.h"
#include <vector>
#include <iostream>

//プレイヤーの順位を保存するクラス
class CRanking
{
public:

	static CRanking* m_instanse;			//インスタンス

	static CRanking* GetInstance()
	{
		if (m_instanse == nullptr)
		{
			m_instanse = new CRanking;
		}

		return m_instanse;
	}

	static void DeleteInstance()
	{
		if (m_instanse != nullptr)
		{
			delete m_instanse;
			m_instanse = nullptr;
		}
	}


private:
	CRanking();
	~CRanking();

	struct tagRankingData
	{
		tagPlayerName			m_name;
		int						m_coin;
	};
	std::vector<tagRankingData> m_rankingData;					//順位データ
public:

	//初期化
	void Init();

	//ステップ
	void Step(CPlayerManager* _playerManager);

	//勝者を取得
	tagPlayerName GetWinnerPlayerName() { return m_rankingData[0].m_name; }

	//プレイヤーの獲得したコインを取得
	int GetPlayerGetCoin(tagPlayerName _playerName);

	//プレイヤーの順位を取得
	int GetPlayerRank(tagPlayerName _playerName);

};

