#include "spawnCoin.h"
#include "../../lib/myMath/myMath.h"
#include "../../system/soundManager.h"
#include "../../data.h"

constexpr int SPAWN_TIME = 12 * 60;		//スポーンするまでの時間

CSpawnCoin::CSpawnCoin()
{
	m_state = ITEM_WAIT;
}

//---------------------
//		 初期化
//---------------------
void CSpawnCoin::Init()
{
	CCoin::Init();

	m_spawnTime = SPAWN_TIME;
	m_spawnPos = ZERO;
}

//---------------------
// 毎フレームする処理
//---------------------
void CSpawnCoin::Step()
{
	CCoin::Step();

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

//---------------------
//	  スポーン処理
//---------------------
void CSpawnCoin::Spawn()
{
	m_isActive = true;
	m_pos = m_spawnPos;
	
	//一回だけ座標を設定する
	MV1SetPosition(m_hndl, m_pos);
}

