#pragma once
#include"../itemShotBase.h"
#include "../../shot/shotManager.h"

class CFireRing:public CItemShotBase
{
private:
	CShotManager* m_shot;

public:
	CFireRing();

	//‰Šú‰»
	void Init(CPlayer* _player);

	//g—p‚µ‚½‚Ìˆ—
	void Use();

};

