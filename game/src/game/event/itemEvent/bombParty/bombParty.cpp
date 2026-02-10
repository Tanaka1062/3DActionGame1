#include "bombParty.h"

constexpr int DROP_BOMB = 7;			//落とす爆弾量
constexpr int DROP_TIME = 45;			//爆弾を落とすまでの間隔

//----------------------
//	  コンストラクタ
//----------------------
CBombPaty::CBombPaty()
{
	Init();
}

//----------------------
//	   デストラクタ
//----------------------
CBombPaty::~CBombPaty()
{
	Exit();
}

//----------------------
//		  初期化
//----------------------
void CBombPaty::Init()
{
	CItemEventBase::Init();
	m_dropTime = 0;
	m_dropBombNum = 0;
}

//----------------------
// 毎フレームする処理
//----------------------
void CBombPaty::Step(VECTOR _center, CItemManager& _itemManager)
{
	m_dropTime++;
	//爆弾を落とす時間を過ぎたら爆弾を落とす
	if (m_dropTime >= DROP_TIME)
	{
		
	}
}

//----------------------
//		終了処理
//----------------------
void CBombPaty::Exit()
{

}

