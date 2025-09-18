#pragma once

#include "../../lib/model/3DObject.h"

//アイテムの名前
enum tagItemName
{
	ITEM_NONE = -1,		//何もない			
	ITEM_FIRE_RING,		//ファイアリング

	ITEM_NUM,			//アイテムの種類
};

//アイテムのベースクラス
class CItemBase :public CObject
{
private:
	tagItemName m_name;	//アイテムの名前

public:
	//コンストラクタ
	CItemBase();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();


};

