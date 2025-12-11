#include "sword.h"

static const int COST = 3;						//‰¿Ši
static const int DURABILITY = 20;				//•Ší‚Ì‘Ï‹v“x

CSword::CSword()
{
	CWeaponBase::Init();
}

CSword::~CSword()
{
	CWeaponBase::Exit();
}

//‰Šú‰»
void CSword::Init()
{
	CWeaponBase::Init();

	m_cost = COST;
	m_itemName = ITEM_SWORD;
	m_id = WEAPON_ID_SWORD;
	m_weaponDurability = DURABILITY;
}

//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
void CSword::Step()
{
	CWeaponBase::Step();

}
