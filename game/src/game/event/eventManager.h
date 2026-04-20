#pragma once
#include "eventBase.h"
#include <iostream>
#include <vector>
#include "../item/itemManager.h"

class CEventManager
{
public:
	//イベントの名前
	enum tagEventName
	{
		EVENT_NONE = -1,			//イベントなし
		EVENT_BOMBPARTY,			//爆弾パーティー
		EVENT_COINPARTY,			//コインパーティー	

		EVENT_NUM,					//イベントの数
	};
private:
	std::vector<CEventBase*>	m_event;		//イベント
	int							m_eventTime;	//イベントが始まるまでの時間
	tagEventName				m_nowEvent;		//現在のイベント

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

	//現在のイベントを取得
	tagEventName GetNowEventName() { return m_nowEvent; }
};

