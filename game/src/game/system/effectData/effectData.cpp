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
		"data/effect/eff.efk",
		"data/effect/eff_loop.efk",
		"data/effect/effect.efk",

	};
	// -------------------------------------

	//エフェクトのロード
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		m_id[i] = CEffekseerCtrl::LoadData(EFFECT_PATH[i]);
	}
}

