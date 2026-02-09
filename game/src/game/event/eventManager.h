#pragma once
#include "eventBase.h"
#include <iostream>
#include <vector>

class CEventManager
{
private:
	std::vector<CEventBase*> m_event;
	int m_eventTime;

public:
	//コンストラクタ・デストラクタ
	CEventManager();
	~CEventManager();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//終了処理
	void Exit();

};

