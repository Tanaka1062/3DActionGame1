#pragma once
#include "../itemEventBase.h"

class CBombPaty :public CItemEventBase
{
private:
	int m_dropTime;			//爆弾を落とす時間
	int m_dropBombNum;		//落とした爆弾の数
public:
	//コンストラクタ・デストラクタ
	CBombPaty();
	~CBombPaty();

	//初期化
	void Init();

	//毎フレームする処理
	void Step(VECTOR _center, CItemManager& _itemManager);

	//終了処理
	void Exit();

};

