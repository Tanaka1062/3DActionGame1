#include "coinParty.h"

constexpr int DROP_COIN = 30;			//落とすコイン量
constexpr int DROP_TIME = 30;			//コインを落とすまでの間隔
constexpr int MAX_DROP_POS_X = 300;		//落とす座標の横
constexpr int MAX_DROP_POS_Z = 300;		//落とす座標の奥行き
constexpr float DROP_POS_Y = 100.0f;		//落とす高さ

//----------------------
//	  コンストラクタ
//----------------------
CCoinPaty::CCoinPaty()
{
	Init();
}

//----------------------
//	   デストラクタ
//----------------------
CCoinPaty::~CCoinPaty()
{
	Exit();
}

//----------------------
//		  初期化
//----------------------
void CCoinPaty::Init()
{
	CItemEventBase::Init();
	m_dropTime = 0;
	m_dropCoinNum = 0;
}

//----------------------
// 毎フレームする処理
//----------------------
void CCoinPaty::Step(VECTOR _center, CItemManager& _itemManager)
{
	m_dropTime++;
	//落とす時間を過ぎたらコインを落とす
	if (m_dropTime >= DROP_TIME)
	{
		VECTOR dropPos = _center;

		//落とす座標を決める
		dropPos.x += static_cast<float>(GetRand(MAX_DROP_POS_X) - (MAX_DROP_POS_X * 0.5f));
		dropPos.z += static_cast<float>(GetRand(MAX_DROP_POS_Z) - (MAX_DROP_POS_Z * 0.5f));
		dropPos.y += DROP_POS_Y;

		//コインを出現させる
		_itemManager.RequestCoin(dropPos);
		
		//出現させたコインのカウントを増やす
		m_dropCoinNum++;

		m_dropTime = 0;
	}

	//出現させたコインの数が出現させる数を超えたら処理を終了する
	if (m_dropCoinNum >= DROP_COIN)
	{
		m_dropCoinNum = 0;
		m_dropTime = 0;
		m_isActive = false;
	}
}

//----------------------
//		終了処理
//----------------------
void CCoinPaty::Exit()
{

}

