#pragma once
#include "coinBase.h"

class CDropCoin : public CCoinBase
{
private:
	int m_deleteTimeCount;			//消えるまでの時間
public:
	//コンストラクタ・デストラクタ
	CDropCoin();
	~CDropCoin();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();
	
	//コインの消失
	void Delete();

};

