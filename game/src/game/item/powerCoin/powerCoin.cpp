#include "powerCoin.h"

CPowerCoin::CPowerCoin()
{

}

CPowerCoin::~CPowerCoin()
{

}

//---------------------
//		 ‰Šú‰»
//---------------------
void CPowerCoin::Init(CPlayer* _player)
{
	CItemBase::Init(_player);

	m_isActive = false;
}

//---------------------
// –ˆƒtƒŒ[ƒ€‚·‚éˆ—
//---------------------
void CPowerCoin::Step()
{
	CItemBase::Step();
}

