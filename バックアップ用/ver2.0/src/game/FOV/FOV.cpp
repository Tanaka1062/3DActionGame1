#include "FOV.h"
#include "../common.h"
#include <math.h>

static const int HIT_TIME = 120;			//当たったかが消えるまでの時間(フレーム)

//------------------------
//		コンストラクタ
//------------------------
CFOV::CFOV()
{
	Init(0.0f);
}

//------------------------
//		初期化
//------------------------
void CFOV::Init(float _rad)
{
	CObject::Init();
	m_rad = _rad;
	m_time = HIT_TIME;
	m_timeCount = 0;
	m_isHit = false;
}

//------------------------
//	毎フレームする処理
//------------------------
void CFOV::Step()
{
	//当たっていた時に時間を数える
	if (m_isHit == true)m_timeCount++;

	//時間経過がすぎると当たっていたかをfalseにする
	if (m_time <= m_timeCount)
	{
		m_timeCount = 0;
		m_isHit = false;
	}
	
#ifdef DEBUG

	//当たり判定を表示
	DrawSphere3D(m_pos, m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG

}

//------------------------
//		更新処理
//------------------------
void CFOV::Update(VECTOR _pos)
{
	m_pos = _pos;

}

//------------------------
//	当たり判定後の処理
//------------------------
void CFOV::HitCalc()
{
	m_timeCount = 0;
	m_isHit = true;
}
