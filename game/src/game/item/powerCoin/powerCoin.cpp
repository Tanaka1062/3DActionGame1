#include "powerCoin.h"

CPowerCoin::CPowerCoin()
{
	m_state = POWER_COIN_WAIT;
	m_playerName = PLAYER_NONE;
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

	m_state = POWER_COIN_WAIT;
	m_playerName = PLAYER_NONE;

	m_isActive = false;

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
void CPowerCoin::HitCalc(tagPlayerName _name)
{
	m_isActive = false;
	m_playerName = _name;
}

