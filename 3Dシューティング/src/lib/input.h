#pragma once

//各キーの割り当て-----------------------------

static int KEY_SHOT = 0b000001;		//ショットボタン
static int KEY_LEFT = 0b000010;		//左ボタン
static int KEY_RIGHT = 0b000100;	//右ボタン
static int KEY_UP = 0b001000;		//上ボタン
static int KEY_DOWN = 0b010000;		//下ボタン

//---------------------------------------------

class CInput
{
private:
	static unsigned int m_nowKey;	//現在のボタン情報
	static unsigned int m_PrevKey;	//1フレーム前のボタン

public:
	//キー入力初期化
	static void Init();
	//キー入力情報更新
	static void Update();
	//キー入力判定（通常判定）
	static bool IsInputRep(unsigned int key);
	//キー入力判定（トリガー判定）
	static bool IsInputTrg(unsigned int key);

};


