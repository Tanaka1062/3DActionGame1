#include "bomb.h"
#include "../../../attack/attackManager.h"

static const int EXPLOSION_TIME = 5 * 60;		//”š”­‚·‚éŽžŠÔ
static const float EXPLOSION_RADIUS = 40.0f;	//”š”­‚Ì”¼Œa
static const int EXPLOSION_ATK = 30;			//”š”­‚ÌUŒ‚—Í


CBomb::CBomb()
{
	m_timeCount = 0;
}

//---------------------
//		  ‰Šú‰»
//---------------------
void CBomb::Init()
{
	CItemObjectBase::Init();

	m_timeCount = 0;
}

//---------------------
// –ˆƒtƒŒ[ƒ€‚·‚éˆ—
//---------------------
void CBomb::Step()
{
	CItemObjectBase::Step();

	if (m_isActive == false)return;

	m_timeCount++;
	//”š”­ŽžŠÔ‚ð‰ß‚¬‚½‚ç”šŽž‚³‚¹‚é
	if (m_timeCount >= EXPLOSION_TIME)
	{
		m_isActive = false;
		m_timeCount = 0;

		Explosion();
	}
}

//---------------------
//		 ‰ó‚ê‚é
//---------------------
void CBomb::Break()
{
	m_timeCount = 0;
	m_isActive = false;

	Explosion();
}

//---------------------
//		 ”š”­
//---------------------
void CBomb::Explosion()
{
	VECTOR explosionPos = m_pos;

	explosionPos.y -= EXPLOSION_RADIUS;

	CAttackManager::Request(explosionPos, EXPLOSION_RADIUS, EXPLOSION_ATK, PLAYER_NONE);

}

