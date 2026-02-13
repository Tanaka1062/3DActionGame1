#pragma once
#include "../../lib/2DUi/2DUi.h"
#include "hpber/hpbarManager.h"
#include "../player/playerManager.h"
#include <iostream>
#include <vector>
#include "../item/itemManager.h"
#include "powerUpGauge/powerUpGouge.h"
#include "time/timeUi.h"
#include "eventText/eventText.h"
#include "../event/eventManager.h"

class CUiGameManager
{
private:
	std::vector<C2DUi*> m_ui;					//UI
	CHpbarManager m_hpbarManager;				//HPバーのマネージャー
	CPowerUpGouge m_powerUpGouge[PLAYER_NUM];	//パワーゲージUi
	CTimeUi m_time;								//時間
	CEventText m_eventText;						//イベントテキスト
public:
	//コンストラクタ・デストラクタ
	CUiGameManager();
	~CUiGameManager();

	void Init(CPlayerManager* _playerManager = nullptr,
		CItemManager* _itemManager = nullptr);
	//ロード
	void Load();
	//毎フレームする処理
	void Step(CEventManager::tagEventName _nowEvent);
	//描写
	void Draw();
	//破棄
	void Exit();

};

