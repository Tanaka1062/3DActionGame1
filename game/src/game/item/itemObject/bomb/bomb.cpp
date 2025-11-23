#include "bomb.h"

static const int EXPLOSION_TIME = 5 * 60;		//”š”­‚·‚éŽžŠÔ

CBomb::CBomb()
{
	m_timeCount = 0;
}

//‰Šú‰»
void CBomb::Init(CPlayer* _player)
{
	CItemObjectBase::Init();

	m_timeCount = 0;
}

//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
void CBomb::Step()
{
	CItemObjectBase::Step();

	if (m_isActive == false)return;

	m_timeCount++;
	//”š”­ŽžŠÔ‚ð‰ß‚¬‚½‚ç”šŽž‚³‚¹‚é
	if (m_timeCount >= EXPLOSION_TIME)
	{
		//m_isActive = false;
		m_timeCount = 0;
	}
}

