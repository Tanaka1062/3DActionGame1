#pragma once
#include"../../lib/2DUi/2DUi.h"

class CScoreText:public C2DUi
{
private:
	int m_scoreCount;	//表示するスコア
public:
	//コンストラクタ・デストラクタ
	CScoreText();
	~CScoreText();

	//初期化
	void Init();
	//画像ロード
	void Load();
	//毎フレームする処理
	void Step(int _score);
	//画像描写
	void Draw();

	//スコアを設定
	void SetScore(int _score) { m_scoreCount = _score; }

};

