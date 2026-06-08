#pragma once
#include"../itemBase.h"
#include "../../player/player.h"

class CWeaponBase :public CItemBase
{
protected:
	PlayerData::tagWeaponId m_id;				//•Ší‚ÌID
	int						m_durability;		//•Ší‚Ì‘Ï‹v“x

public:
	CWeaponBase();
	virtual ~CWeaponBase();

	//‰Šú‰»
	void Init();

	//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
	void Step();

	//“–‚½‚Á‚½‚Ìˆ—
	void HitCalc(CObject* _hitObject);

};

