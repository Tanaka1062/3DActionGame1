#include "box.h"

CBox::CBox()
{

}

//-------------------------
//		   ‰Šú‰»
//-------------------------
void CBox::Init()
{
	CItemObjectBase::Init();
}

//-------------------------
//	 –ˆƒtƒŒ[ƒ€‚·‚éˆ—
//-------------------------
void CBox::Step()
{
	CItemObjectBase::Step();

	if (m_isLift == true)
	{
		CPlayer* player = nullptr;
		player = dynamic_cast<CPlayer*>(m_owner);

		m_rot.y = player->GetRot().y;
	}
}
