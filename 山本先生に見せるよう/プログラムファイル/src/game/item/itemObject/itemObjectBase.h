#pragma once
#include "../itemBase.h"

class CItemObjectBase : public CItemBase
{
protected:
	bool m_isLift;			//持ち上げられているかどうか
	bool m_isDrop;			//アイテムが落とされているかどうか

public:
	//コンストラクタ
	CItemObjectBase();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();

	//当たった時の処理
	virtual void HitCalc(CObject* _hitObject);

	//持ち上げられているかを取得
	bool GetIsLift() { return m_isLift; }

protected:

	//壊れる
	virtual void Break();

};

