#pragma once
#include"../itemBase.h"
#include "../../player/player.h"

class CWeaponBase :public CItemBase
{
protected:
	tagWeaponId m_id;			//•Ší‚ÌID
	int m_weaponDurability;		//•Ší‚Ì‘Ï‹v“x

public:
	CWeaponBase();
	~CWeaponBase();

	//‰Šú‰»
	void Init();

	//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
	void Step();

	//“–‚½‚Á‚½‚Ìˆ—
	void HitCalc(CObject* _hitObject);

};

