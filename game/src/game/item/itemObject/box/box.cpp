#include "box.h"
#include "../../../data.h"

static const int SPAWN_TIME = 5 * 60;		//スポーンするまでの時間

CBox::CBox()
{

}

//-------------------------
//		   初期化
//-------------------------
void CBox::Init()
{
	CItemObjectBase::Init();

	m_spawnTime = 0;
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
//		スポーン処理
//-------------------------
void CBox::Spawn()
{
	m_isActive = true;
	m_pos = m_spawnPos;
}

