#include "itemObjectBase.h"

CItemObjectBase::CItemObjectBase()
{
	m_isLift = false;
}

//‰Šú‰»
void CItemObjectBase::Init(CPlayer* _player = nullptr)
{
	CItemBase::Init(_player);

	m_isLift = false;
}

//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
void CItemObjectBase::Step()
{

}

