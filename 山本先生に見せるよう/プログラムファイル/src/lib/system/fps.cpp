#include <DxLib.h>
#include "fps.h"

//定義関連----------------------
constexpr float FRAME_PATE = 60.0f;									//1秒辺りのフレーム数
constexpr float FRAME_RATE_MILLI_SECOND = 1000.0f / FRAME_PATE;		//何ミリ秒で1フレームか
//------------------------------

float CFps::m_frameRate;	//今のフレームレートを保存
int CFps::m_nowTime;		//現在時間
int CFps::m_prevTime;		//ひとつ前の時間
int CFps::m_prevDrawTime;	//1つ前の描画したPC時間
int CFps::m_count;			//カウント用


// 初期化関数
void CFps::Init()
{
	m_frameRate = 0.0f;
	m_nowTime = GetNowCount();
	m_prevTime = 0;
	m_count = 0;
	m_prevDrawTime = 0;
}

// 次のフレームに進めていいか
bool CFps::IsNextFrame()
{
	//現在の時間を取得
	m_nowTime = GetNowCount();
	//前回の時間と今回の時間の差を取得
	int difTime = m_nowTime - m_prevTime;

	//前回の時間から指定したフレーム分、時間が通過したかチェック
	if (difTime >= FRAME_RATE_MILLI_SECOND)
	{
		return true;
	}
	else return false;
}

// FPS更新処理
void CFps::Update()
{
	//ここまで来たら時間を更新
	m_prevTime = m_nowTime;
}

//　FPS表示関数
void CFps::Print()
{
	//カウントを増やす
	m_count++;
	//前回の時間と今回の時間の差を取得
	int difTime = m_nowTime - m_prevDrawTime;

	//差異が1秒以上あれば計算開始（１秒に１回フレームの表示を更新）
	if (difTime >= 1000)
	{
		//ある程度正常に動いていたら、m_countは60,000になっているはず
		float frameCount = (float)(m_count * 1000);
		//表示するfpsを更新　(理想は60,0)
		m_frameRate = frameCount / difTime;
		//カウントは0に初期化
		m_count = 0;
		//ひとつ前の時間を更新
		m_prevDrawTime = m_nowTime;
	}

	//文字の表示　引数は「横の位置」「縦の位置」「色」「」
	//DrawFormatString(10, 10, GetColor(0, 255, 0), "FPS:%.2f", m_frameRate);
}