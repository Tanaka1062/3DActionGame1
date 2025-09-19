#pragma once
#include <iostream>
#include <list>
#include "itemBase.h"
#include "../data.h"

using namespace std;


//アイテムマネージャークラス
class CItemManager
{
private:
	list<CItemBase*> m_item;	//アイテムのクラス
	int m_hndl[ITEM_NUM];		//アイテムのモデルハンドル
public:
	//コンストラクタ・デストラクタ
	CItemManager();
	~CItemManager();

	//初期化
	void Init();
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

};

