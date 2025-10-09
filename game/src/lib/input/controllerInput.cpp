#include "controllerInput.h"
#include<DxLib.h>

static const int BUTTON_PATH[BUTTON_NUM] = {
	PAD_INPUT_DOWN,
	PAD_INPUT_LEFT,
	PAD_INPUT_RIGHT,
	PAD_INPUT_UP,
	PAD_INPUT_1,
	PAD_INPUT_2,
	PAD_INPUT_3,
	PAD_INPUT_4,
	PAD_INPUT_5,
	PAD_INPUT_6,
	PAD_INPUT_7,
	PAD_INPUT_8,
	PAD_INPUT_9,
	PAD_INPUT_10,

};

unsigned int CControllerInput::m_nowButton;
unsigned int CControllerInput::m_beforeButton;
int CControllerInput::m_LX;
int CControllerInput::m_LY;
int CControllerInput::m_RX;
int CControllerInput::m_RY;

//--------------------------------
//		コンストラクタ
//--------------------------------
CControllerInput::CControllerInput()
{
	Init();
}

//--------------------------------
//	コントローラー入力初期化
//--------------------------------
void CControllerInput::Init()
{
	m_nowButton = 0;
	m_beforeButton = 0;
	m_LX = 0;
	m_LY = 0;
}

//--------------------------------
//	コントローラー入力情報更新
//--------------------------------
void CControllerInput::Update()
{
	//一フレーム前の情報を保存
	m_beforeButton = m_nowButton;
	//最新情報を初期化
	m_nowButton = 0;

	//現在の入力情報を取得
	m_nowButton = GetJoypadInputState(DX_INPUT_PAD1);

	//レバーの入力情報を取得
	DINPUT_JOYSTATE leverInput;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &leverInput);
	m_LX = leverInput.X;
	m_LY = leverInput.Y;
	m_RX = leverInput.Rx;
	m_RY = leverInput.Ry;
}

//--------------------------------
//	ボタン入力判定（通常判定）
//--------------------------------
bool CControllerInput::IsRep(tagControllerButton _button)
{
	if ((m_nowButton & BUTTON_PATH[_button]) != 0) return true;
	else return false;

}

//--------------------------------
//	ボタン入力判定（トリガー判定）
//--------------------------------
bool CControllerInput::IsTrg(tagControllerButton _button)
{
	if ((m_nowButton & BUTTON_PATH[_button]) && !(m_beforeButton & BUTTON_PATH[_button])) return true;
	else return false;

}

