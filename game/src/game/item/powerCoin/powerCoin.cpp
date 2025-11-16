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
//		 初期化
//---------------------
void CPowerCoin::Init(CPlayer* _player)
{
	CItemBase::Init(_player);

	m_state = POWER_COIN_WAIT;
	m_playerName = PLAYER_NONE;

	m_isActive = false;

}

//---------------------
// 毎フレームする処理
//---------------------
void CPowerCoin::Step()
{
	CItemBase::Step();
}

//---------------------
//	当たった時の処理
//---------------------
void CPowerCoin::HitCalc(tagPlayerName _name)
{
	m_isActive = false;
	m_playerName = _name;
}

//---------------------
//	コインのドロップ
//---------------------
void CPowerCoin::Drop(VECTOR _pos, float _rotY)
{
	m_pos = _pos;
	m_state = POWER_COIN_FLYING;
	m_isActive = true;
	m_playerName = PLAYER_NONE;

}
