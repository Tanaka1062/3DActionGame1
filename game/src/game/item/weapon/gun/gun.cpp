#include "gun.h"

constexpr int COST = 2;						//‰¿Ši
constexpr int DURABILITY = 12;				//•Ší‚Ì‘Ï‹v“x

CGun::CGun()
{
	CWeaponBase::Init();
}

CGun::~CGun()
{
	CWeaponBase::Exit();
}

//‰Šú‰»
void CGun::Init()
{
	CWeaponBase::Init();

	m_cost = COST;
	m_itemName = ITEM_GUN;
	m_id = WEAPON_ID_GUN;
	m_weaponDurability = DURABILITY;

	m_rot.x += 0.2f;
}

//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
void CGun::Step()
{
	CWeaponBase::Step();
	m_rot.y += 0.01;

}
