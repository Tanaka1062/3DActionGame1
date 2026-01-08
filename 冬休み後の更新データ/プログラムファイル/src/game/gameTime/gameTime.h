#pragma once

class CGameTime
{
public:

	static CGameTime* m_instance;		//インスタンス


	static CGameTime* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new CGameTime;
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
	CGameTime();
	~CGameTime();

	int m_timeCount;					//タイムカウント
	bool m_isEnd;						//終わったかフラグ
	int m_startTime;					//開始時間

public:
	
	//初期化
	void Init();

	//ステップ
	void Step();

	//時間が終了したかを取得
	bool GetTimeEnd() { return m_isEnd; }

	//時間を取得
	int GetTime() { return m_timeCount; }

};

