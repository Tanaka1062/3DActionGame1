#include "box.h"
#include "../../../data.h"

constexpr int SPAWN_TIME = 12 * 60;		//スポーンするまでの時間
constexpr int ATK = 10;					//攻撃力

CBox::CBox()
{
	Init();
}

//-------------------------
//		   初期化
//-------------------------
void CBox::Init()
{
	CItemObjectBase::Init();

	m_spawnTime = SPAWN_TIME;
	m_spawnPos = V_ZERO;
	m_isSpawn = false;
}

//-------------------------
//	 毎フレームする処理
//-------------------------
void CBox::Step()
{
	CItemObjectBase::Step();

	if (m_isLift == true)
	{
		m_rot.y = m_owner->GetRot().y;
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
	m_rot = V_ZERO;
}

//-------------------------
//		   壊れる
//-------------------------
void CBox::Break()
{
	m_isActive = false;

	CAttackManager* attack = CAttackManager::GetInstance();
	attack->Request(m_pos, m_rad, ATK,0, PLAYER_NONE);
}

