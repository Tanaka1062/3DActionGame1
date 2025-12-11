#pragma once
#include "../player/playerData.h"
#include "../player/playerManager.h"

//勝利したプレイヤーを保存するクラス
class CWinner
{
public:

	static CWinner* m_instanse;			//インスタンス

	static CWinner* GetInstance()
	{
		if (m_instanse == nullptr)
		{
			m_instanse = new CWinner;
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
	CWinner();
	~CWinner();

	tagPlayerName m_winnerPlayer;		//勝利したプレイヤー

public:

	//初期化
	void Init();

	//ステップ
	void Step(CPlayerManager* _playerManager);

	//時間が終了したかを取得
	tagPlayerName GetWinnerPlayerName() { return m_winnerPlayer; }

};

