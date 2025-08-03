#include "controllerInput.h"
#include<DxLib.h>

unsigned int CControllerInput::m_nowButton;
unsigned int CControllerInput::m_beforeButton;

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

}

//--------------------------------
//	ボタン入力判定（通常判定）
//--------------------------------
bool CControllerInput::IsRep(unsigned int _button)
{
	if ((m_nowButton & _button) != 0) return true;
	else return false;

}

//--------------------------------
//	ボタン入力判定（トリガー判定）
//--------------------------------
bool CControllerInput::IsTrg(unsigned int _button)
{
	if ((m_nowButton & _button) && !(m_beforeButton & _button)) return true;
	else return false;

}
