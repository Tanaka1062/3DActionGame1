#include "gun.h"

constexpr int COST = 0;						//‰¿Ši
constexpr int DURABILITY = 10;				//•Ší‚Ì‘Ï‹v“x

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
}

//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
void CGun::Step()
{
	CWeaponBase::Step();

}
