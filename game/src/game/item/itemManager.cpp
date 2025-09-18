#include "itemManager.h"

static const int ITEM_NUM = 1;	//アイテムの個数

//-----------------------
//	  コンストラクタ
//-----------------------
CItemManager::CItemManager()
{
	for (int i = 0; i < ITEM_NUM; i++)
	{
		
	}
}

//-----------------------
//	  デストラクタ
//-----------------------
CItemManager::~CItemManager()
{

}

//-----------------------
//		初期化
//-----------------------
void CItemManager::Init()
{
	
}

//-----------------------
//	  モデルロード
//-----------------------
void CItemManager::Load()
{
	//アイテムのモデルのパスを管理======
	const char* MODEL_PATH[ITEM_NUM] =
	{
		"data/model/item/fireRing.mv1",

	};
	//==================================

}

//-----------------------
//	毎フレームする処理
//-----------------------
void CItemManager::Step()
{

}

//-----------------------
//		数値の更新
//-----------------------
void CItemManager::Update()
{

}

//-----------------------
//	オブジェクトの描写
//-----------------------
void CItemManager::Draw()
{

}

//-----------------------
//		終了処理
//-----------------------
void CItemManager::Exit()
{

}
