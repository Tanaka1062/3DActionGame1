#include "eventManager.h"
#include "itemEvent/bombParty/bombParty.h"
#include "itemEvent/coinParty/coinParty.h"

constexpr int EVENT_START_TIME = 50 * 60;			//爆弾を落とすまでの間隔

//---------------------------
//		コンストラクタ
//---------------------------
CEventManager::CEventManager()
{
	m_eventTime = 0;
	m_nowEvent = EVENT_NONE;
}

//---------------------------
//		 デストラクタ
//---------------------------
CEventManager::~CEventManager()
{
	Exit();
}

//---------------------------
//			初期化
//---------------------------
void CEventManager::Init()
{
	//イベントを作成
	m_event.push_back(new CBombPaty);
	m_event.push_back(new CCoinPaty);

	for (int event_i = 0; event_i < m_event.size(); event_i++)
	{
		m_event[event_i]->Init();
	}

	m_eventTime = 0;
	m_nowEvent = EVENT_NONE;
}

//---------------------------
//	  毎フレームする処理
//---------------------------
void CEventManager::Step(VECTOR _center, CItemManager& _itemManager)
{
	//実行されているイベントを数える
	int activeEventNum = 0;
	for (int event_i = 0; event_i < m_event.size(); event_i++)
	{
		if (m_event[event_i]->GetActive() == false)continue;
		
		activeEventNum++;
		if (m_event[event_i]->GetType() == EVENT_ITEM_TYPE)
		{
			CItemEventBase* itemEvent = dynamic_cast<CItemEventBase*>(m_event[event_i]);

			itemEvent->Step(_center,_itemManager);
		}
	}

	//イベントが一つも実行されていない場合現在のイベントを初期化する
	if (activeEventNum <= 0)
	{
		m_nowEvent = EVENT_NONE;
	}

	m_eventTime++;
	//イベント開始時間になったらイベントを始める
	if (m_eventTime >= EVENT_START_TIME)
	{
		int rand = GetRand(EVENT_NUM - 1);

		m_event[rand]->SetActive(true);
		m_eventTime = 0;
		m_nowEvent = static_cast<tagEventName>(rand);
	}
}

//---------------------------
//		   終了処理
//---------------------------
void CEventManager::Exit()
{
	for (int event_i = 0; event_i < m_event.size(); event_i++)
	{
		m_event[event_i]->Exit();
		delete m_event[event_i];
	}
	m_event.clear();
}

