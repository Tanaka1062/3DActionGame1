#include "playMapBase.h"

constexpr int			SHAKE_AMOUNT = 2;					//揺れる大きさ
constexpr float			FALL_MAX = -300.0f;					//最大の落下位置


//------------------------
//	ステージの移動処理
//------------------------
void CPlayMapBase::StageMove(VECTOR _moveSpeed)
{

	if (m_stageId - 1 >= 0)
	{
		if (m_stage[m_stageId - 1]->GetActive() == false)return;

		VECTOR vec = m_stage[m_stageId - 1]->GetPos();
		m_stage[m_stageId - 1]->SetPos(VAdd(vec, _moveSpeed));

		if (m_stage[m_stageId - 1]->GetPos().y <= FALL_MAX)
		{
			m_stage[m_stageId - 1]->SetActive(false);
			m_isStageFall = false;
		}
	}
}

//------------------------
//	ステージの揺れる処理
//------------------------
void CPlayMapBase::StageShake(VECTOR _pos)
{

	if (m_stageId - 1 >= 0)
	{
		if (m_stage[m_stageId - 1]->GetActive() == false)return;

		VECTOR shake = { 0 };
		shake.x = static_cast<float>(GetRand(SHAKE_AMOUNT) - (SHAKE_AMOUNT * 0.5));
		shake.z = static_cast<float>(GetRand(SHAKE_AMOUNT) - (SHAKE_AMOUNT * 0.5));

		VECTOR vec = VAdd(_pos, shake);
		m_stage[m_stageId - 1]->SetPos(vec);
	}
}
