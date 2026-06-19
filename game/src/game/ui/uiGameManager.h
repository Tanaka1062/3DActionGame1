#pragma once
#include "../../lib/2D/2DObject.h"
#include "../player/playerManager.h"
#include <iostream>
#include <vector>
#include "../item/itemManager.h"
#include "time/timeUi.h"
#include "eventText/eventText.h"
#include "../event/eventManager.h"
#include "playerStatusPanel/playerStatusPanel.h"

class CUiGameManager
{
private:
	CTimeUi					m_time;								//時間
	CEventText				m_eventText;						//イベントテキスト
	CPlayerStatusPanel		m_playerStautusPanel[PLAYER_NUM];	//プレイヤーのステータスパネル
public:
	//コンストラクタ・デストラクタ
	CUiGameManager();
	~CUiGameManager();

	void Init(CPlayerManager* _playerManager = nullptr,
		CItemManager* _itemManager = nullptr);
	//ロード
	void Load();
	//毎フレームする処理
	void Step(CEventManager::tagEventName _nowEvent,CPlayerManager& _playerManager);
	//描写
	void Draw();
	//破棄
	void Exit();

};

