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
void CAttack::Init(float _rad, float _length)
{
	CObject::Init();
	m_rad = _rad;;
	m_time = 0;
	m_timeCount = 0;
	m_length = _length;
	m_isActive = false;
	m_isAttackable = false;
}

//------------------------
//	毎フレームする処理
//------------------------
void CAttack::Step()
{
	DrawSphere3D(m_pos, m_rad, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);

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

	//値を更新
	m_rot = _rot;

	//攻撃判定の座標設定
	m_pos.x = -sinf(m_rot.y) * m_length;
	m_pos.y = 0.0f;
	m_pos.z = -cosf(m_rot.y) * m_length;

	m_pos = VAdd(m_pos, _pos);

}

//------------------------
//		攻撃の呼び出し
//------------------------
void CAttack::Request(VECTOR _pos, VECTOR _rot, int _time)
{
	//値を入力
	m_rot = _rot;
	m_time = _time;
	m_isActive = true;

	//攻撃判定の座標設定
	m_pos.x = -sinf(m_rot.y) * m_length;
	m_pos.y = _pos.y;
	m_pos.z = -cosf(m_rot.y) * m_length;

	m_pos = VAdd(m_pos, _pos);

}
