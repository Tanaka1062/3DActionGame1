#include "box.h"
#include "../../../data.h"

static const int SPAWN_TIME = 12 * 60;		//スポーンするまでの時間
static const float ATK = 10.0f;				//攻撃力

CBox::CBox()
{

}

//-------------------------
//		   初期化
//-------------------------
void CBox::Init()
{
	CItemObjectBase::Init();

	m_spawnTime = SPAWN_TIME;
	m_spawnPos = ZERO;
}

//-------------------------
//	 毎フレームする処理
//-------------------------
void CBox::Step()
{
	CItemObjectBase::Step();

	if (m_isLift == true)
	{
		CPlayer* player = nullptr;
		player = dynamic_cast<CPlayer*>(m_owner);

		m_rot.y = player->GetRot().y;

	}

	if (m_isActive == false)
	{
		m_spawnTime++;
		if (m_spawnTime >= SPAWN_TIME)
		{
			Spawn();
			m_spawnTime = 0;
		}
	}
}

//-------------------------
//	 マップに触れたとき
//-------------------------
void CBox::HitMapCalc()
{
	//アイテムがドロップした状態だとアイテムを消す
	if (m_isDrop == true)
	{
		m_isActive = false;
	}
}

//-------------------------
//		スポーン処理
//-------------------------
void CBox::Spawn()
{
	m_isActive = true;
	m_pos = m_spawnPos;
	m_rot = ZERO;
}

//-------------------------
//		   壊れる
//-------------------------
void CBox::Break()
{
	m_isActive = false;
	CAttackManager::Request(m_pos, m_rad, ATK, PLAYER_NONE);
}

