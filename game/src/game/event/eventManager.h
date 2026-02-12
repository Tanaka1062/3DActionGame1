#pragma once
#include "eventBase.h"
#include <iostream>
#include <vector>
#include "../item/itemManager.h"

class CEventManager
{
private:
	std::vector<CEventBase*> m_event;		//イベント
	int m_eventTime;						//イベントが始まるまでの時間

public:
	//コンストラクタ・デストラクタ
	CEventManager();
	~CEventManager();

	//初期化
	void Init();

	//毎フレームする処理
	void Step(VECTOR _center, CItemManager& _itemManager);

	//終了処理
	void Exit();

};

