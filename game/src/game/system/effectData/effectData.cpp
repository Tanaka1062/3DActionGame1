#include"effectData.h"
#include"../../lib/effekseer/effekseer.h"

int CEffectData::m_id[EFFECT_NUM];

//コンストラクタ
CEffectData::CEffectData()
{
	Init();
}

//初期化
void CEffectData::Init()
{
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		m_id[i] = -1;
	}
}

//ロード
void CEffectData::Load()
{
	// ロードするエフェクトを管理----------
	const char* EFFECT_PATH[EFFECT_NUM] = {
		"data/effect/hit.efk",
		"data/effect/heal_effect.efk",
		"data/effect/eff_loop.efk",
		"data/effect/effect.efk",
		"data/effect/explosion.efk",
		"data/effect/itemSpawn.efk",
		"data/effect/shockWave.efk",
		"data/effect/coinGet.efk",
		"data/effect/ax_effect.efk",
		"data/effect/handAttack.efk",
	};
	// -------------------------------------

	//エフェクトのロード
	for (int effect_i = 0; effect_i < EFFECT_NUM; effect_i++)
	{
		m_id[effect_i] = CEffekseerCtrl::LoadData(EFFECT_PATH[effect_i]);
	}
}


