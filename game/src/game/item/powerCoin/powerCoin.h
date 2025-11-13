#pragma once
#include "../itemBase.h"

//プレイヤーのアドレスが必要ないのに継承のせいで持っている(HACK)
class CPowerCoin : public CItemBase
{
private:
	bool m_isGet;			//プレイヤーが持っているかどうか
public:
	CPowerCoin();
	~CPowerCoin();

	//初期化
	void Init(CPlayer* _player = nullptr);

	//毎フレームする処理
	void Step();

	//当たった時の処理
	void HitCalc();

	//当たったかどうかを取得
	bool GetIsGet() { return m_isGet; }

};

