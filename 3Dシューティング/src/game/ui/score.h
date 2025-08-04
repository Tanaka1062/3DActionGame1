#pragma once
#include"../../lib/2DUi/2DUi.h"

class CScore:public C2DUi
{
private:
	int m_scoreNow;		//現在のスコア
	int m_scoreCount;	//表示するスコア
public:
	//コンストラクタ・デストラクタ
	CScore();
	~CScore();

	//初期化
	void Init();
	//画像ロード
	void Load();
	//毎フレームする処理
	void Step();
	//画像描写
	void Draw();

};

