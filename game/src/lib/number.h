#pragma once

#include <DxLib.h>

constexpr int NUM_SIZE = 64;	//数字のサイズ

class CNumber
{
private:
	static int m_hndl[10];		//画像ハンドル

public:
	// データを初期化
	static void Init();
	// 画像データをロード
	static void Load();
	// 終了前に行う
	static void Exit();

	//数字を表示する
	static void RequestNumber(int x, int y, int number, float size);

};

