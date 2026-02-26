#pragma once
#include "../eventBase.h"
#include"../../item/itemManager.h"

class CItemEventBase :public CEventBase
{
private:

public:
	//コンストラクタ・デストラクタ
	CItemEventBase ();
	virtual ~CItemEventBase ();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step(VECTOR _center,CItemManager& _itemManager);

	//終了処理
	virtual void Exit();

};

