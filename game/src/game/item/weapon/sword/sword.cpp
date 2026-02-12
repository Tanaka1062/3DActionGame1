#include "sword.h"

constexpr int COST = 0;						//‰¿Ši
constexpr int DURABILITY = 20;				//•Ší‚Ì‘Ï‹v“x

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

	m_rot.x += 0.2f;
}

//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
void CSword::Step()
{
	CWeaponBase::Step();
	m_rot.y += 0.01f;

}
