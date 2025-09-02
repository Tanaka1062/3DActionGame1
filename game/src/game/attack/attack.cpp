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
void CAttack::Init(float _rad, float _length,
	float _attackable_rad, int _waitTime, int _hitNum)
{
	CObject::Init();
	m_rad = _rad;;
	m_attackWaitTime = 0;
	m_attackTime = 0;
	m_attackWaitTime = _waitTime;
	m_coolDownTime = 0;
	m_timeCount = 0;
	m_length = _length;
	m_hitCount = _hitNum;
	m_state = WAIT;
	m_isActive = false;
	m_attackable.m_pos = { 0.0f,0.0f,0.0f };
	m_attackable.m_rad = _attackable_rad;
	m_attackable.m_isPossible = false;
}

//------------------------
//	毎フレームする処理
//------------------------
void CAttack::Step()
{

	switch (m_state)
	{
	case WAIT:
		m_timeCount++;
		if (m_timeCount >= m_attackWaitTime)
		{

		}
		break;
	case ATTACK:
		m_timeCount++;
		//時間がすぎたら攻撃を消す
		if (m_timeCount >= m_attackTime)
		{
			m_attackTime = 0;
			m_timeCount = 0;
			m_isActive = false;
			m_state = COOLDOWN;
		}
		break;
	case COOLDOWN:
		m_timeCount++;
		//時間が過ぎたら待機状態に
		if (m_timeCount >= m_coolDownTime)
		{
			m_timeCount = 0;
			m_state = WAIT;
		}
		break;
	}

	m_timeCount++;

	
#ifdef DEBUG

	//攻撃中は当たり判定の色が赤色になる
	if (m_state == ATTACK)
	{
		//攻撃中範囲の視覚化
		DrawSphere3D(m_pos, m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
	}
	else
	{
		//攻撃範囲の視覚化
		DrawSphere3D(m_pos, m_rad, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
	}

	//攻撃可能範囲の視覚化
	DrawSphere3D(m_attackable.m_pos, m_attackable.m_rad, 16, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
#endif // DEBUG

}

//------------------------
//		更新処理
//------------------------
void CAttack::Update(VECTOR _pos, VECTOR _rot)
{

	//攻撃角度を更新
	m_rot = _rot;

	//攻撃判定の座標設定
	m_pos.x = -sinf(m_rot.y) * m_length;
	m_pos.y = 0.0f;
	m_pos.z = -cosf(m_rot.y) * m_length;

	m_pos = VAdd(m_pos, _pos);

	//攻撃可能範囲の座標を設定
	m_attackable.m_pos = _pos;

}

//------------------------
//		攻撃の呼び出し
//------------------------
void CAttack::Request(VECTOR _pos, VECTOR _rot, int _attackTime,
	int _coolDownTime)
{
	//攻撃待機状態以外は攻撃を呼び出さない
	if (m_state != WAIT)return;

	//値を入力
	m_rot = _rot;
	m_attackTime = _attackTime;
	m_coolDownTime = _coolDownTime;
	m_isActive = true;
	
	//状態を攻撃中に設定
	m_state = ATTACK;

	//攻撃判定の座標設定
	m_pos.x = -sinf(m_rot.y) * m_length;
	m_pos.y = _pos.y;
	m_pos.z = -cosf(m_rot.y) * m_length;

	m_pos = VAdd(m_pos, _pos);

}
