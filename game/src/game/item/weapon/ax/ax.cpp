#include "ax.h"

static const int COST = 3;						//‰¿Ši
static const int DURABILITY = 20;				//•Ší‚Ì‘Ï‹v“x

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
}

//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
void CAx::Step()
{
	CWeaponBase::Step();

}
