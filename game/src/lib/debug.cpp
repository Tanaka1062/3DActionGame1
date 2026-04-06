#include "debug.h"

float CDebug::m_numY[3];

CDebug::CDebug()
{
	m_numY[0] = 0.0f;
	m_numY[1] = 0.0f;
	m_numY[2] = 0.0f;
}

CDebug::~CDebug()
{

}

void CDebug::Draw()
{
	DrawFormatString(120, 120, GetColor(255, 0, 0), "プレイヤ%f", m_numY[0]);
	DrawFormatString(120, 180, GetColor(255, 0, 0), "マップ%f", m_numY[1]);
	DrawFormatString(120, 240, GetColor(255, 0, 0), "マップ%f", m_numY[2]);
}

