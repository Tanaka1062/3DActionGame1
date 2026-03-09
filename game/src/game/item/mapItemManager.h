#pragma once
#include <iostream>
#include <vector>
#include "itemBase.h"
#include "../data.h"
#include "itemObject/box/box.h"
#include "../map/mapBase.h"

//アイテムマネージャークラス
class CMapItemManager
{
private:
	std::vector<std::unique_ptr<CItemBase>> m_item;
	int m_hndl;											//アイテムのモデルハンドル

public:
	//コンストラクタ・デストラクタ
	CMapItemManager();
	~CMapItemManager();

	//初期化
	void Init();
	//モデルロード
	void Load(CMapBase* _map);
	//毎フレームする処理
	void Step();
	//終了処理
	void Exit();

	//アイテムの数を取得
	int GetItemNum() { return static_cast<int>(m_item.size()); }

	//アイテムのアドレスを取得
	std::unique_ptr<CItemBase> GetItem(int _num);

};

