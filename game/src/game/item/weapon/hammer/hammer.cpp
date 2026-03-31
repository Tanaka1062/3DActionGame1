#include "hammer.h"

constexpr int COST = 0;						//‰¿Ši
constexpr int DURABILITY = 20;				//•Ší‚Ì‘Ï‹v“x

CHammer::CHammer()
{
	CWeaponBase::Init();
}

CHammer::~CHammer()
{
	CWeaponBase::Exit();
}

//‰Šú‰»
void CHammer::Init()
{
	CWeaponBase::Init();

	m_cost = COST;
	m_itemName = ITEM_HAMMER;
	m_id = WEAPON_ID_HAMMER;
	m_weaponDurability = DURABILITY;

	m_rot.x += 0.2f;
}

