#include "harbAmulent.h"

static const int ADD_HP = 10;		//‘Ì—Í‚Ì‰ñ•œ—Ê

//-------------
//	 ‰Šú‰»
//-------------
void CHarbAmulent::Init(CPlayer* _player)
{
	CItemBase::Init(_player);
	m_type = TYPE_USE;
	m_name = ITME_HARB_AMULENT;
}

//-------------
//Žg—p‚µ‚½Žž‚Ìˆ—
//-------------
void CHarbAmulent::Use()
{
	m_player->AddHp(ADD_HP);
}
