#include "itemObjectBase.h"

CItemObjectBase::CItemObjectBase()
{
	m_isLift = false;
}

//‰Šú‰»
void CItemObjectBase::Init(CPlayer* _player)
{
	CItemBase::Init(_player);

	m_isLift = false;
}

//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
void CItemObjectBase::Step()
{
	CItemBase::Step();
}

