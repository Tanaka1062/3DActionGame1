#include "number.h"

//定義関連----------------------
static int NUM_SIZE = 64;	//数字のサイズ
//------------------------------

int Number::m_hndl[10];		//画像ハンドル

// データを初期化
void Number::Init()
{
	for (int i = 0;i < 10; i++)
	{
		m_hndl[i] = -1;
	}
}

// 画像データをロード
void Number::Load()
{
	int success;
	//もうすでに画像がロードされていたら-1でなくなっている
	if (m_hndl[0] == -1)
	{
		//画像データ読み込み
		//失敗していたら-1が変数に入る
		success = LoadDivGraph("data/graphics/game/number.png",
			10, 10, 1, NUM_SIZE, NUM_SIZE, m_hndl);
	}

}

// 終了前に行う
void Number::Exit()
{
	for (int i = 0;i < 10; i++)
	{
		//ハンドルが-1でなければ、何かしらロードがされているはず
		if (m_hndl[i] != -1)
		{
			//画像メモリ上から破棄する
			DeleteGraph(m_hndl[i]);
			m_hndl[i] = -1;
		}

	}

}

//数字を表示する
void Number::RequestNumber(int x, int y, int number, float size)
{
	DrawRotaGraph(x, y, size, 0.0, m_hndl[number], TRUE);

}
