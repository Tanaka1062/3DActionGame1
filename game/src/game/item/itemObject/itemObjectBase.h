#pragma once
#include "../itemBase.h"

class CItemObjectBase : public CItemBase
{
protected:
	bool m_isLift;			//‚¿ã‚°‚ç‚ê‚Ä‚¢‚é‚©‚Ç‚¤‚©

public:
	CItemObjectBase();

	//‰Šú‰»
	virtual void Init();

	//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
	virtual void Step();

	//“–‚½‚Á‚½‚Ìˆ—
	virtual void HitCalc(CObject* _hitObject);

	//‚¿ã‚°‚ç‚ê‚Ä‚¢‚é‚©‚ğæ“¾
	bool GetIsLift() { return m_isLift; }

protected:

	//‰ó‚ê‚é
	virtual void Break();

};

