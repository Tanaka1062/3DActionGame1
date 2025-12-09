#pragma once
#include"../itemShotBase.h"
#include "../../shot/shotManager.h"

class CFireRing:public CItemShotBase
{
private:

public:
	CFireRing();

	//‰Šú‰»
	void Init(CPlayer* _player);

	//g—p‚µ‚½‚Ìˆ—
	void Use(CShotManager* _shot);

};

