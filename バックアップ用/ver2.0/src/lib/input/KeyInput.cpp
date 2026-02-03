#include "keyInput.h"
#include <DxLib.h>

unsigned int CKeyInput::m_nowKey;
unsigned int CKeyInput::m_beforeKey;

//--------------------------------
//		コンストラクタ
//--------------------------------
CKeyInput::CKeyInput() 
{
	Init();
}

//--------------------------------
//		キー入力初期化
//--------------------------------
void CKeyInput::Init()
{
	m_nowKey = 0;
	m_beforeKey = 0;
}
//--------------------------------
//		キー入力情報更新
//--------------------------------
void CKeyInput::Update()
{
	//最新情報は1フレーム前の情報になる
	m_beforeKey = m_nowKey;
	//いったん最新情報は初期化
	m_nowKey = 0;
	
	//決定キー情報取得
	if ((GetMouseInput()& MOUSE_INPUT_LEFT)!= 0) m_nowKey |= KEY_SELECT;
	//キャンセルキー情報取得
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) m_nowKey |= KEY_CANCEL;
	//ノーマルキー情報取得
	if (CheckHitKey(KEY_INPUT_1) != 0) m_nowKey |= KEY_NORMAL;
	//スーパーキー情報取得
	if (CheckHitKey(KEY_INPUT_2) != 0) m_nowKey |= KEY_SUPER;
	//ハイパーキー情報取得
	if (CheckHitKey(KEY_INPUT_3) != 0) m_nowKey |= KEY_HYPER;

}
//--------------------------------
//	キー入力判定（通常判定）
//--------------------------------
bool CKeyInput::IsRep(unsigned int _key)
{
	if ((m_nowKey & _key) != 0) return true;
	else return false;
}
//--------------------------------
//	キー入力判定（トリガー判定）
//--------------------------------
bool CKeyInput::IsTrg(unsigned int _key)
{
	if ((m_nowKey & _key) && !(m_beforeKey & _key)) return true;
	else return false;
}

