#pragma once

//コントローラーのボタン一覧
enum tagControllerButton
{
	BUTTON_DOWN,		//下ボタン
	BUTTON_LEFT,		//左ボタン
	BUTTON_RIGHT,		//右ボタン
	BUTTON_UP,			//上ボタン
	BUTTON_A,			//Aボタン
	BUTTON_B,			//Bボタン
	BUTTON_X,			//Xボタン
	BUTTON_Y,			//Yボタン
	BUTTON_LB,			//LBボタン
	BUTTON_RB,			//RBボタン
	BUTTON_BACK,		//BACKボタン
	BUTTON_START,		//STARTボタン
	BUTTON_LSTICK,		//Lスティック押し込み
	BUTTON_RSTICK,		//Rスティック押し込み

	BUTTON_NUM,			//ボタンの数
};

class CControllerInput
{
private:
	unsigned int	m_nowButton;	//現在のボタン情報
	unsigned int	m_beforeButton;	//1フレーム前のボタン
	int				m_LX;			//左レバーを左右の入力情報
	int				m_LY;			//左レバーを上下の入力情報
	int				m_RX;			//右レバーを左右の入力情報
	int				m_RY;			//右レバーを上下の入力情報
	int				m_controllerId;	//コントローラーのID情報
public:
	//コンストラクタ
	CControllerInput();

	//コントローラー入力初期化
	void Init();
	//コントローラー入力情報更新
	void Update();
	//ボタン入力判定（通常判定）
	bool IsRep(tagControllerButton _button);
	//ボタン入力判定（トリガー判定）
	bool IsTrg(tagControllerButton _button);

	//レバーの値は1～0～(-1)の間で出力する
	//左レバーの左右の入力情報を取得
	float GetLX() { return static_cast<float>(m_LX) / 1000.0f; }
	//左レバーの上下の入力情報を取得
	float GetLY() { return static_cast<float>(m_LY) / 1000.0f; }
	//右レバーの左右の入力情報を取得
	float GetRX() { return static_cast<float>(m_RX) / 1000.0f; }
	//右レバーの上下の入力情報を取得
	float GetRY() { return static_cast<float>(m_RY) / 1000.0f; }

	//コントローラーのIDを取得
	int GetId() { return m_controllerId; }
	//コントローラーのIDを設定
	void SetId(int _id) { m_controllerId = _id; }
};

