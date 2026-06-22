#include "number.h"

using namespace std;

array<int,CNumber::NUMBER_NUM> CNumber::m_hndl;		//画像ハンドル

// データを初期化
void CNumber::Init()
{
	for (int hndl_i = 0; hndl_i < 10; hndl_i++)
	{
		m_hndl[hndl_i] = -1;
	}
}

// 画像データをロード
void CNumber::Load()
{
	int success;
	//もうすでに画像がロードされていたら-1でなくなっている
	if (m_hndl[0] == -1)
	{
		//画像データ読み込み
		//失敗していたら-1が変数に入る
		success = LoadDivGraph("data/graphic/ui/number.png",
			NUMBER_NUM, NUMBER_NUM, 1, NUMBER_SIZE, NUMBER_SIZE, &m_hndl[0]);
	}

}

// 終了前に行う
void CNumber::Exit()
{
	for (int hndl_i = 0; hndl_i < m_hndl.size(); hndl_i++)
	{
		//ハンドルが-1でなければ、何かしらロードがされているはず
		if (m_hndl[hndl_i] != -1)
		{
			//画像メモリ上から破棄する
			DeleteGraph(m_hndl[hndl_i]);
			m_hndl[hndl_i] = -1;
		}

	}

}

//数字を表示する
void CNumber::RequestNumber(float _x, float _y, int _number, float _size, int _digit)
{
	//何桁あるかを調べる-------------------------------------------
	int digit = 1;
	int num = 10;
	while (true)
	{
		//マイナスではない場合桁数を増やす
		if (_number - num >= 0)
		{
			digit++;
			num *= 10;
		}
		else
		{
			break;
		}
	}

	//引数よりも桁数が少ない場合は引数側を使う
	if (digit <= _digit)
	{
		digit = _digit;
	}
	//-------------------------------------------------------------


	//横にずらす量
	float x = NUMBER_SIZE * _size;
	//表示する数字
	int number = _number;

	//桁数分ループする
	for (int number_i = 0; number_i < digit; number_i++)
	{
		//割り算に使う数字
		int num1 = 1;
		for (int digit_j = 0; digit_j < digit - (number_i + 1); digit_j++)
		{
			num1 *= 10;
		}

		//ほしい桁だけ取り出す
		int num2 = number / num1;

		//数字を表示
		DrawRotaGraph(static_cast<int>(_x + x * number_i), static_cast<int>(_y), _size, 0.0, m_hndl[num2], TRUE);

		//いらない数字を消す
		number -= num2 * num1;

	}
}

//数字を表示する
void CNumber::RequestNumber(VECTOR _pos, int _number, float _size, int _digit)
{
	RequestNumber(_pos.x, _pos.y, _number, _size,_digit);
}

