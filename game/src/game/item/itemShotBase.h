#pragma once
#include "itemBase.h"
#include "../shot/shotManager.h"

//弾発射するアイテムのベースクラス
class CItemShotBase :public CItemBase
{
protected:

public:
	//コンストラクタ
	CItemShotBase();

	//初期化
	virtual void Init();

	//使用した時の処理
	virtual void Use(CShotManager* _shot);

};

