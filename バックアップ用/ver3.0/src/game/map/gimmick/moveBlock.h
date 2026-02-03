#pragma once
#include "gimmickBase.h"

class CMoveBlock :public CGimmickBase
{
private:

public:
	//コンストラクタ・デストラクタ
	CMoveBlock();
	~CMoveBlock();

	//初期化
	void Init();
	
	//毎フレームする処理
	void Step();
};

