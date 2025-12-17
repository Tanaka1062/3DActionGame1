#include "gameTime.h"
#include <DxLib.h>
#include "../data.h"

CGameTime* CGameTime::m_instance = nullptr;

constexpr int END_TIME = 3 * 60;	//終わるまでの時間

CGameTime::CGameTime()
{
	m_timeCount = 0;
	m_isEnd = false;
}

CGameTime::~CGameTime()
{

}

//初期化
void CGameTime::Init()
{
	m_timeCount = END_TIME;
	m_isEnd = false;
	m_startTime = -1;
}

//ステップ
void CGameTime::Step()
{
	if (m_startTime == -1)
	{
		m_startTime = GetNowCount();
	}

	//一秒たったら制限時間を進める
	if (GetNowCount() - m_startTime >= 1000)
	{
		m_startTime = GetNowCount();
		m_timeCount--;
	}

	if (m_timeCount <= 0)
	{
		m_isEnd = true;
	}
}

