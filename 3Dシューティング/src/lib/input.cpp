#include "input.h"
#include <DxLib.h>


unsigned int CInput::m_nowKey;	//現在のボタン情報
unsigned int CInput::m_PrevKey;	//1フレーム前のボタン


//キー入力初期化
void CInput::Init()
{
	m_nowKey = m_PrevKey = 0;
}

//キー入力情報更新
void CInput::Update()
{
	//最新情報は1フレーム前の情報になる
	m_PrevKey = m_nowKey;
	//いったん最新情報は初期化
	m_nowKey = 0;
	
	//ショットキー情報取得
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) m_nowKey |= KEY_SHOT;
	//左キー情報取得
	if (CheckHitKey(KEY_INPUT_A) != 0) m_nowKey |= KEY_LEFT;
	//右キー情報取得
	if (CheckHitKey(KEY_INPUT_D) != 0) m_nowKey |= KEY_RIGHT;
	//上キー情報取得
	if (CheckHitKey(KEY_INPUT_W) != 0) m_nowKey |= KEY_UP;
	//下キー情報取得
	if (CheckHitKey(KEY_INPUT_S) != 0) m_nowKey |= KEY_DOWN;

}

//キー入力判定（通常判定）
bool CInput::IsInputRep(unsigned int key)
{
	if ((m_nowKey & key) != 0) return TRUE;
	else return FALSE;
}

//キー入力判定（トリガー判定）
bool CInput::IsInputTrg(unsigned int key)
{
	if ((m_nowKey & key) && !(m_PrevKey & key)) return TRUE;
	else return FALSE;
}

