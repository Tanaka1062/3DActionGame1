#pragma once

class CScoreData
{
private:
	static int m_score;	//スコア

public:
	//コンストラクタ
	CScoreData();

	//初期化
	static void Init();

	///スコアを増やす
	static void Add(int _addNum) { m_score += _addNum; }

	//スコアを取得
	static int GetScore() { return m_score; }

};

