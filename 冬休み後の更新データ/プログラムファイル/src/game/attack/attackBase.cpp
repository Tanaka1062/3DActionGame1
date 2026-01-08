#include "attackBase.h"

//----------------------
//	  コンストラクタ
//----------------------
CAttackBase::CAttackBase()
{
	Init();
}

//----------------------
//		  初期化
//----------------------
void CAttackBase::Init()
{
	CObject::Init();
	m_isAttack = false;
	m_isPushed = false;
	m_atk = 0;
	m_blown = 0;
	m_num = 0;
	m_numCount = 0;
	m_nextTime = 0;
	m_timeCount = 0;
	m_attackName = PLAYER_NONE;
	m_objectTypy = OBJECT_ATTACK;
}

//----------------------
//	オブジェクトの描写
//----------------------
void CAttackBase::Draw()
{
	CObject::Draw();
}

//----------------------
//		更新処理
//----------------------
void CAttackBase::Update()
{
	//攻撃をしていたら攻撃の回数を増やす
	if (m_isAttack == true)
	{
		m_isAttack = false;
		m_numCount++;
		//攻撃の回数が上限に到達したら攻撃をやめる
		if (m_numCount >= m_num)
		{
			m_isActive = false;
		}
	}
	//攻撃をしていなかったら時間を進める
	else
	{
		m_timeCount++;
		//時間が過ぎたら攻撃している状態に変える
		if (m_timeCount >= m_nextTime)
		{
			m_isAttack = true;
			m_timeCount = 0;
		}
	}
}

//----------------------
//	  攻撃の呼び出し
//----------------------
void CAttackBase::Request(VECTOR _pos, float _rad, int _atk, int _blown, tagPlayerName _name, int _num, int _nextTime)
{
	m_pos = _pos;
	m_rad = _rad;
	m_atk = _atk;
	m_blown = _blown;
	m_attackName = _name;
	m_num = _num;
	m_nextTime = _nextTime;
	m_isActive = true;
	m_isAttack = true;
}

