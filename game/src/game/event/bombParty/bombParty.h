#pragma once
#include "../eventBase.h"

class CBombPaty :public CEventBase
{
private:

public:
	//コンストラクタ・デストラクタ
	CBombPaty();
	~CBombPaty();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//終了処理
	void Exit();

};

