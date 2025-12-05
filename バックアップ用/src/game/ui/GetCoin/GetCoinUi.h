#pragma once
#include "../../lib/2DUi/2DUi.h"
#include <DxLib.h>
#include "../../item/itemManager.h"

static const int GRAPHIC_ALL_NUM = 2;

class CGetCoinUi
{
private:
	VECTOR m_pos;
	int m_hndl[COIN_MAX_NUM][GRAPHIC_ALL_NUM];
	bool m_IsGetCoin[COIN_MAX_NUM];
	CItemManager* m_itemManager;

public:
	CGetCoinUi();
	~CGetCoinUi();

	//初期化
	void Init(VECTOR _pos,CItemManager* _itemManager);
	//ロード
	void Load();
	//毎フレームする処理
	void Step(tagPlayerName _playerName);
	//描写
	void Draw();
	//破棄
	void Exit();

};

