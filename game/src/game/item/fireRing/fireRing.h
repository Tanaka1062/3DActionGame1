#pragma once
#include "../itemBase.h"
#include "../../shot/shotManager.h"

class CFireRing:public CItemBase
{
private:
	CShotManager* m_shot;

public:
	CFireRing();
	~CFireRing();

	//‰Šú‰»
	void Init(CPlayer* _player);

	//g—p‚µ‚½‚Ìˆ—
	void Use();

};

