#pragma once
#include "../../lib/model/3DObject.h"

class CGimmickBase :public CObject
{
private:

public:
	CGimmickBase();
	virtual ~CGimmickBase();

	//ƒ‚ƒfƒ‹‚Ìƒ[ƒh
	virtual void Load(const char* _filePath,const char* _mapFrame,int _mapFrameNum);



};

