#include "eventBase.h"

//-----------------------
//	   コンストラクタ
//-----------------------
CEventBase::CEventBase()
{
	Init();
}

//-----------------------
//	    デストラクタ
//-----------------------
CEventBase::~CEventBase()
{

}

//-----------------------
//		  初期化
//-----------------------
void CEventBase::Init()
{
	m_timeCount = 0;
	m_isActive = false;
	m_type = EVENT_TYPE_NONE;
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CEventBase::Step()
{

}

//-----------------------
//		 終了処理
//-----------------------
void CEventBase::Exit()
{

}

