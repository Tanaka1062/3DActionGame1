#pragma once
#include "../itemBase.h"
#include "../../player/player.h"
#include "../../player/playerData.h"

class CPowerCoin : public CItemBase
{
private:
	tagPlayerName m_playerName;	//誰が持っているか

public:
	CPowerCoin();
	~CPowerCoin();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//数値の更新
	void Update();

	//当たった時の処理
	//_name		:どのプレイヤーが触れたかを取得
	void HitCalc(CObject* _hitObject);

	//持っているプレイヤーの名前
	tagPlayerName GetPlayerName() { return m_playerName; }
	
	//コインのドロップ
	void Drop(VECTOR _pos,float _rotY);

	//コインの消失
	void Delete();

};

