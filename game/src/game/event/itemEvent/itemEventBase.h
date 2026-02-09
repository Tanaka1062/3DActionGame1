#pragma once
#include "../eventBase.h"

class CItemEventBase :public CEventBase
{
private:

public:
	//コンストラクタ・デストラクタ
	CItemEventBase ();
	~CItemEventBase ();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();

	//終了処理
	virtual void Exit();

};

