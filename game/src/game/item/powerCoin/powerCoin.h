#pragma once
#include "../itemBase.h"
#include "../../player/player.h"
#include "../../player/playerData.h"

enum tagPowerCoinState
{
	POWER_COIN_FLYING,		//飛んでいる状態
	POWER_COIN_WAIT,		//待機状態

};

//プレイヤーのアドレスが必要ないのに継承のせいで持っている(HACK)
class CPowerCoin : public CItemBase
{
private:
	tagPowerCoinState m_state;	//状態
	tagPlayerName m_playerName;	//誰が持っているか

public:
	CPowerCoin();
	~CPowerCoin();

	//初期化
	void Init(CPlayer* _player = nullptr);

	//毎フレームする処理
	void Step();

	//当たった時の処理
	//_name		:どのプレイヤーが触れたかを取得
	void HitCalc(tagPlayerName _name);

	//状態を取得
	tagPowerCoinState GetState() { return m_state; }

	//持っているプレイヤーの名前
	tagPlayerName GetPlayerName() { return m_playerName; }
	
	//コインのドロップ
	void Drop(VECTOR _pos,float _rotY);

};

