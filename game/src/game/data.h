#pragma once
#include <DxLib.h>

//定義関連----------------------

static int WINDOW_SIZE_X = 1040;			//ウィンドウサイズ横
static int WINDOW_SIZE_Y = 640;				//ウィンドウサイズ縦

static VECTOR ZERO = { 0.0f,0.0f,0.0f };	//VECTORの初期化用

//------------------------------


class CData
{

private:
	static int m_score;		//ゲームのスコア

public:
	CData() { m_score = 0; }
	~CData(){}

	//スコアを取得
	static int GetScore() { return m_score; }
	//スコアを設定
	static void SetScore(int _score) { m_score = _score; }
	//スコア加算
	static void AddScore(int _addScore) { m_score += _addScore; }
};

