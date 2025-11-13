#include "powerCoin.h"

CPowerCoin::CPowerCoin()
{
	m_isGet = false;
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
	m_isGet = false;
}

//---------------------
// –ˆƒtƒŒ[ƒ€‚·‚éˆ—
//---------------------
void CPowerCoin::Step()
{
	CItemBase::Step();
}

//---------------------
//	“–‚½‚Á‚½‚Ìˆ—
//---------------------
void CPowerCoin::HitCalc()
{
	m_isActive = false;
	m_isGet = true;
}

