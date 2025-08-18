#include "attack.h"
#include "../common.h"
#include <math.h>

//------------------------
//		コンストラクタ
//------------------------
CAttack::CAttack()
{
	Init();
}

//------------------------
//		初期化
//------------------------
void CAttack::Init()
{
	CObject::Init();
	m_time = 0;
	m_timeCount = 0;
	m_length = 0;
	m_isActive = false;
}

//------------------------
//	毎フレームする処理
//------------------------
void CAttack::Step()
{
	if (m_isActive == false)return;

	m_timeCount++;

	//時間がすぎたら攻撃を消す
	if (m_timeCount>= m_time)
	{
		m_time = 0;
		m_timeCount = 0;
		m_isActive = false;
	}
	
#ifdef DEBUG

	DrawSphere3D(m_pos, m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG

}

//------------------------
//		更新処理
//------------------------
void CAttack::Update(VECTOR _pos, VECTOR _rot)
{
	if (m_isActive == false)return;

	//値を更新
	m_rot = _rot;

	//攻撃判定の座標設定
	m_pos.x = -sinf(m_rot.y) * m_length;
	m_pos.y = _pos.y;
	m_pos.z = -cosf(m_rot.y) * m_length;

	m_pos = VAdd(m_pos, _pos);

}

//------------------------
//		攻撃の呼び出し
//------------------------
void CAttack::Request(VECTOR _pos, VECTOR _rot, float _rad, float _length, int _time)
{
	//値を入力
	m_rot = _rot;
	m_length = _length;
	m_rad = _rad;
	m_time = _time;
	m_isActive = true;

	//攻撃判定の座標設定
	m_pos.x = -sinf(m_rot.y) * m_length;
	m_pos.y = _pos.y;
	m_pos.z = -cosf(m_rot.y) * m_length;

	m_pos = VAdd(m_pos, _pos);

}
