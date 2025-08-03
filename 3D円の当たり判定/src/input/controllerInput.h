#pragma once

class CControllerInput
{
private:
	static unsigned int m_nowButton;		//現在のボタン情報
	static unsigned int m_beforeButton;		//1フレーム前のボタン

public:
	//コンストラクタ
	CControllerInput();

	//コントローラー入力初期化
	static void Init();
	//コントローラー入力情報更新
	static void Update();
	//ボタン入力判定（通常判定）
	static bool IsRep(unsigned int _button);
	//ボタン入力判定（トリガー判定）
	static bool IsTrg(unsigned int _button);

};

