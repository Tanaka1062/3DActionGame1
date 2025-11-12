#pragma once
#include "../itemBase.h"

//プレイヤーのアドレスが必要ないのに継承のせいで持っている(HACK)
class CPowerCoin : public CItemBase
{
private:

public:
	CPowerCoin();
	~CPowerCoin();

	//初期化
	void Init(CPlayer* _player = nullptr);

	//毎フレームする処理
	void Step();

};

