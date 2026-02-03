#pragma once

//各キーの割り当て-----------------------------
#define KEY_SELECT	(0b000001)	//決定ボタン
#define KEY_CANCEL	(0b000010)	//キャンセルボタン
#define KEY_NORMAL	(0b000100)	//ノーマルボタン
#define KEY_SUPER	(0b001000)	//スーパーボタン
#define KEY_HYPER	(0b010000)	//ハイパーボタン
//---------------------------------------------

class CKeyInput
{
private:
	static unsigned int m_nowKey;		//現在のボタン情報
	static unsigned int m_beforeKey;	//1フレーム前のボタン

public:
	CKeyInput();

	//キー入力初期化
	static void Init();
	//キー入力情報更新
	static void Update();
	//キー入力判定（通常判定）
	static bool IsRep(unsigned int _key);
	//キー入力判定（トリガー判定）
	static bool IsTrg(unsigned int _key);

};


