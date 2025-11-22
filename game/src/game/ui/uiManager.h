#pragma once
#include "../../lib/2DUi/2DUi.h"
#include "hpber/hpbarManager.h"
#include "../player/playerManager.h"
#include <iostream>
#include <vector>
#include "GetCoin/GetCoinUi.h"
#include "../item/itemManager.h"

using namespace std;

class CUiManager
{
private:
	vector<C2DUi*> m_ui;				//UI
	CHpbarManager m_hpbarManager;		//HPバーのマネージャー
	CGetCoinUi m_getCoinUi[PLAYER_NUM];	//コインの取得Ui
public:
	//コンストラクタ・デストラクタ
	CUiManager();
	~CUiManager();

	void Init(CPlayerManager* _playerManager = nullptr,
		CItemManager* _itemManager = nullptr);
	//ロード
	void Load();
	//毎フレームする処理
	void Step();
	//描写
	void Draw();
	//破棄
	void Exit();

};

