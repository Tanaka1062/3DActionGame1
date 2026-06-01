#include "fade.h"
#include <DxLib.h>
#include "../../game/data.h"

//定義関連----------------------
constexpr int FADE_SPEED = 10;		//フェードの速さ
//------------------------------
 
tagFadeSteate CFade::m_state;
int CFade::m_count;

//フェードを初期化する
void CFade::Init()
{
	m_state = FADE_NON;
	m_count = 0;
}
//フェード処理更新
void CFade::Step()
{
	//状態に合わせて行動変化
	//実際に処理するのは下記の二つだけ
	switch (m_state)
	{
	case FADE_IN:
		//徐々に数字を減らして明るくする
		m_count -= FADE_SPEED;
		if (m_count <= 0)
		{
			m_count = 0;
			m_state = FADE_NON;
		}
		break;

	case FADE_OUT:
		//徐々に数字を増やして暗くする
		m_count += FADE_SPEED;
		if (m_count >= 255)
		{
			m_count = 255;
			m_state = FADE_OUT_WAIT;
		}
		break;
	}
}
//フェード用の画像描画
void CFade::Draw()
{
	switch (m_state)
	{case FADE_IN:
	case FADE_OUT:
	case FADE_OUT_WAIT:
		//まずはここでアルファ値をセットする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_count);
		//フェード用の黒い四角を表示
		DrawBox(0, 0, static_cast<int>(WINDOW_SIZE_X), static_cast<int>(WINDOW_SIZE_Y),
			GetColor(0, 0, 0), TRUE);

		//他の画像に影響を出さないように、初期設定に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		break;
	}
}

//----------------------
//フェードイン呼び出し
//----------------------
void CFade::RequestFadeIn()
{
	if (m_state == FADE_IN)return;

	m_state = FADE_IN;
	m_count = 255;

}

//-----------------------
//フェードアウト呼び出し
//-----------------------
void CFade::RequestFadeOut()
{
	if (m_state == FADE_OUT)return;

	m_state = FADE_OUT;
	m_count = 0;

}

//-----------------------------
//フェードインが終了しているか
//-----------------------------
bool CFade::IsEndFadeIn()
{
	if (m_state == FADE_IN)
		return false;
	else
		return true;
}

//-------------------------------
//フェードアウトが終了しているか
//-------------------------------
bool CFade::IsEndFadeOut()
{
	if (m_state == FADE_OUT)
		return false;
	else
		return true;
}

