#pragma once

#include <DxLib.h>
#include <iostream>
#include <array>

class CNumber
{
public:
	static constexpr int NUMBER_SIZE = 64;		//数字のサイズ
private:
	static constexpr int NUMBER_NUM = 10;		//数字の画像の数

	static std::array<int,NUMBER_NUM> m_hndl;	//画像ハンドル

public:
	// データを初期化
	static void Init();
	// 画像データをロード
	static void Load();
	// 終了前に行う
	static void Exit();

	//数字を表示する(float用)
	//_x		:一番左の数字の座標X
	//_y		:一番左の数字の座標Y
	//_number	:表示する数字
	//_size		:数字の大きさ(入力しない場合は1.0f)
	//_digit	:何桁表示するか(入力しない場合は1)
	//メモ		:指定した桁数を超えた場合全ての数字が表示されるように桁数が増えます
	static void RequestNumber(float _x, float _y, int _number, float _size = 1.0f,int _digit = 1);

	//数字を表示する(VECTOR用)
	//_pos		:一番左の数字の座標
	//_number	:表示する数字
	//_size		:数字の大きさ(入力しない場合は1.0f)
	//_digit	:何桁表示するか(入力しない場合は1)
	//メモ		:指定した桁数を超えた場合全ての数字が表示されるように桁数が増えます
	static void RequestNumber(VECTOR _pos, int _number, float _size = 1.0f, int _digit = 1);

};

