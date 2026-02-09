#pragma once
#include "../../lib/2DUi/2DUi.h"

class CCountDown :public C2DUi
{
public:
	enum tagCountNumber
	{
		COUNT_0,						//カウント０
		COUNT_1,						//カウント１
		COUNT_2,						//カウント２
		COUNT_3,						//カウント３

		COUNT_NUM,						//カウントの数
	};

private:

	int m_count;						//カウント
	int m_timeCount;					//タイムカウント
	int m_countHndl[COUNT_NUM];			//カウントの画像ハンドル
	bool m_isEnd;						//カウントが終了したかフラグ
public:
	//コンストラクタ・デストラクタ
	CCountDown();
	~CCountDown();

	//初期化
	void Init();

	//画像ロード
	void Load();

	//毎フレームする処理
	void Step(bool _isCountStart);

	//画像描写
	void Draw();

	//終了処理
	void Exit();

	//カウントが終了したかを取得
	bool GetIsEnd() { return m_isEnd; }

};

