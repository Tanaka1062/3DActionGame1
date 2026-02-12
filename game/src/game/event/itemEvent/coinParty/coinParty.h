#pragma once
#include "../itemEventBase.h"

class CCoinPaty :public CItemEventBase
{
private:
	int m_dropTime;			//コインを落とす時間
	int m_dropCoinNum;		//落としたコインの数
public:
	//コンストラクタ・デストラクタ
	CCoinPaty();
	~CCoinPaty();

	//初期化
	void Init();

	//毎フレームする処理
	void Step(VECTOR _center, CItemManager& _itemManager);

	//終了処理
	void Exit();

};

