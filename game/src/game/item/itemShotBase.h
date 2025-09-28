#pragma once
#include "itemBase.h"
#include "../shot/shotManager.h"

//弾発射するアイテムのベースクラス
class CItemShotBase :public CItemBase
{
protected:
	CShotManager* m_shot;			//弾のマネージャーのアドレス保存用

public:
	//コンストラクタ
	CItemShotBase();

	//初期化
	virtual void Init(CPlayer* _player,CShotManager* _shot);

};

