#pragma once
#include "../itemBase.h"
#include "../../player/player.h"
#include "../../player/playerData.h"

class CCoin : public CItemBase
{
private:

public:
	CCoin();
	~CCoin();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//数値の更新
	void Update();

	//当たった時の処理
	//_name		:どのプレイヤーが触れたかを取得
	void HitCalc(CObject* _hitObject);
	
	//コインの消失
	void Delete();

};

