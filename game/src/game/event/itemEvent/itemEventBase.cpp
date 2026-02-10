#include "itemEventBase.h"

//--------------------------
//		コンストラクタ
//--------------------------
CItemEventBase::CItemEventBase()
{
	Init();
}

//--------------------------
//		  デストラクタ
//--------------------------
CItemEventBase::~CItemEventBase()
{
	Exit();
}

//--------------------------
//			初期化
//--------------------------
void CItemEventBase::Init()
{
	CEventBase::Init();
	m_type = EVENT_ITEM_TYPE;
}

//--------------------------
//	  毎フレームする処理
//--------------------------
void CItemEventBase::Step(VECTOR _center, CItemManager& _itemManager)
{

}

//--------------------------
//		  終了処理
//--------------------------
void CItemEventBase::Exit()
{

}

