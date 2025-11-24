#pragma once
#include "../itemObjectBase.h"

class CBomb : public CItemObjectBase
{
private:
	int m_timeCount;		//時間カウント
public:
	CBomb();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

private:
	//壊れる
	void Break();

	//爆発
	void Explosion();
};

