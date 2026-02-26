#include "bombParty.h"

constexpr int DROP_BOMB = 10;			//落とす爆弾量
constexpr int DROP_TIME = 65;			//爆弾を落とすまでの間隔
constexpr int MAX_DROP_POS_X = 300;		//落とす座標の横
constexpr int MAX_DROP_POS_Z = 300;		//落とす座標の奥行き
constexpr float DROP_POS_Y = 100.0f;	//落とす高さ

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
	//落とす時間を過ぎたら爆弾を落とす
	if (m_dropTime >= DROP_TIME)
	{
		VECTOR dropPos = _center;

		//落とす座標を決める
		dropPos.x += static_cast<float>(GetRand(MAX_DROP_POS_X) - (MAX_DROP_POS_X * 0.5f));
		dropPos.z += static_cast<float>(GetRand(MAX_DROP_POS_Z) - (MAX_DROP_POS_Z * 0.5f));
		dropPos.y += DROP_POS_Y;

		//爆弾を出現させる
		_itemManager.RequestItem(ITEM_BOMB,dropPos);
		
		//出現させた爆弾のカウントを増やす
		m_dropBombNum++;

		m_dropTime = 0;
	}

	//出現させた爆弾の数が出現させる数を超えたら処理を終了する
	if (m_dropBombNum >= DROP_BOMB)
	{
		m_dropBombNum = 0;
		m_dropTime = 0;
		m_isActive = false;
	}
}

//----------------------
//		終了処理
//----------------------
void CBombPaty::Exit()
{

}

