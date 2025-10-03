#pragma once
#include"../itemBase.h"

class CHarbAmulent :public CItemBase
{
private:

public:
	CHarbAmulent();

	//‰Šú‰»
	void Init(CPlayer* _player);

	//g—p‚µ‚½‚Ìˆ—
	void Use() override;

};

