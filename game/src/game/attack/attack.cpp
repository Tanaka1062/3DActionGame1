#include "attack.h"
#include "../common.h"

//コンストラクタ
CAttack::CAttack()
{
	Init();
}

//初期化
void CAttack::Init()
{
	CObject::Init();
	m_time = 0;
	m_timeCount = 0;
	m_isActive = false;
}

//毎フレームする処理
void CAttack::Step()
{
	if (m_isActive == false)return;

	m_timeCount++;
	if (m_timeCount >= m_time)
	{
		Init();
	}
	
#ifdef DEBUG

	DrawSphere3D(m_pos, m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG

}

//攻撃の呼び出し
void CAttack::Request(const CObject& _obj, float _rad, float _length, int _time)
{

	m_time = _time;
	m_isActive = true;
}
