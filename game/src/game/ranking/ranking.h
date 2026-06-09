#pragma once
#include "../player/playerData.h"
#include "../player/playerManager.h"
#include <vector>
#include <iostream>

//プレイヤーの順位を保存するクラス
class CRanking
{
private:
	static CRanking* m_instance;			//インスタンス

public:

	static CRanking* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new CRanking;
		}

		return m_instance;
	}

	static void DeleteInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}


private:
	//コンストラクタ
	CRanking();

	struct tagRankingData
	{
		tagPlayerName						m_name;
		int									m_coin;
	};
	std::vector<tagRankingData>				m_rankingData;		//順位データ
	struct tagPlayerData
	{
		int									m_coinNum;						
	};
	std::vector<std::vector<tagPlayerData>>	m_playerData;		//プレイヤーデータ
public:

	//初期化
	void Init(int _stageNum = 0);

	//ステップ
	void Step(CPlayerManager* _playerManager,int _stageId);

	//勝者を取得
	tagPlayerName GetWinnerPlayerName() { return m_rankingData[0].m_name; }

	//プレイヤーの獲得したコインを取得
	int GetPlayerGetCoin(tagPlayerName _playerName);

	//プレイヤーの順位を取得
	int GetPlayerRank(tagPlayerName _playerName);

	//プレイヤーデータの数
	int GetPlayerDataNum() { return static_cast<int>(m_playerData.size()); }

	//プレイヤーデータを取得
	tagPlayerData GetPlayerData(int _dataId,int _playerId) { return m_playerData[_dataId][_playerId]; }
};

