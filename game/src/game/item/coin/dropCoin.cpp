#include "dropCoin.h"

constexpr int DELETE_TIME = 10 * 60;		//消えるまでの時間

//---------------------
//	 コンストラクタ
//---------------------
CDropCoin::CDropCoin()
{
	m_state = ITEM_WAIT;
}

//---------------------
//	   デストラクタ
//---------------------
CDropCoin::~CDropCoin()
{
	CCoinBase::Exit();
}

//---------------------
//		 初期化
//---------------------
void CDropCoin::Init()
{
	CCoinBase::Init();
	m_deleteTimeCount = 0;
}

//---------------------
// 毎フレームする処理
//---------------------
void CDropCoin::Step()
{
	CCoinBase::Step();

	m_deleteTimeCount++;
	if (m_deleteTimeCount >= DELETE_TIME)
	{
		Delete();
		m_isActive = false;
	}
}

//---------------------
//	   コインの消失
//---------------------
void CDropCoin::Delete()
{
	CCoinBase::Delete();
	m_deleteTimeCount = 0;
}

