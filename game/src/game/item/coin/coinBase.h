#pragma once
#include "../itemBase.h"

class CCoinBase : public CItemBase
{
private:
public:
	//コンストラクタ・デストラクタ
	CCoinBase();
	virtual ~CCoinBase();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();

	//当たった時の処理
	//_name		:どのプレイヤーが触れたかを取得
	void HitCalc(CObject* _hitObject);
	
	//コインの消失
	virtual void Delete();

};

