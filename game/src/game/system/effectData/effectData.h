#pragma once


enum tagEffectKind	//エフェクトの種類
{
	EFFECT_ATTACK,			//攻撃エフェクト
	EFFECT_HEAL,			//回復エフェクト
	EFFECT2,				//エフェクト２
	EFFECT3,				//エフェクト３
	EFFECT_EXPLOSION,		//爆発エフェクト
	EFFECT_SPAWNITEM,		//アイテムスポーンエフェクト
	EFFECT_SHOCK_WAVE,		//衝撃波エフェクト
	EFFECT_COIN_GET,		//コイン獲得エフェクト
	EFFECT_AX,

	EFFECT_NUM,				//エフェクトの数
};

class CEffectData
{
private:
	static int m_id[EFFECT_NUM];			//エフェクトのID
public:
	//コンストラクタ
	CEffectData();

	//初期化
	static void Init();

	//ロード
	static void Load();

	//エフェクトのIDを取得
	static int GetId(tagEffectKind _kind) { return m_id[_kind]; }

};

