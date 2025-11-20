#pragma once
#include "../itemBase.h"

class CItemObjectBase : public CItemBase
{
private:
	bool m_isLift;			//‚¿ã‚°‚ç‚ê‚Ä‚¢‚é‚©‚Ç‚¤‚©

public:
	CItemObjectBase();

	//‰Šú‰»
	virtual void Init(CPlayer* _player = nullptr);

	//–ˆƒtƒŒ[ƒ€‚·‚éˆ—
	virtual void Step();

	//‚¿ã‚°‚ç‚ê‚Ä‚¢‚é‚©‚ğæ“¾
	bool GetIsLift() { return m_isLift; }
};

