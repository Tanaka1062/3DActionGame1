#include "itemBase.h"

static const float ROT_SPEED = 0.05f;	//回転速度

//コンストラクタ
CItemBase::CItemBase()
{
	Init();
}

//初期化
void CItemBase::Init()
{
	CObject::Init();

	//アイテムを何もないに設定
	m_name = ITEM_NONE;
}

//毎フレームする処理
void CItemBase::Step()
{
	//少しずつ回転させる
	m_rot.y += ROT_SPEED;
}
