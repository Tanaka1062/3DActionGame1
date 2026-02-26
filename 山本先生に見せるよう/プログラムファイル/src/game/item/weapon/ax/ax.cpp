#include "ax.h"

constexpr int COST = 0;						//‰¿Ši
constexpr int DURABILITY = 15;				//•Ší‚Ì‘Ï‹v“x

CAx::CAx()
{
	CWeaponBase::Init();
}

CAx::~CAx()
{
	CWeaponBase::Exit();
}

//‰Šú‰»
void CAx::Init()
{
	CWeaponBase::Init();

	m_cost = COST;
	m_itemName = ITEM_AX;
	m_id = WEAPON_ID_AX;
	m_weaponDurability = DURABILITY;

	m_rot.x += 0.2f;
}

