#include"scoreData.h"

int CScoreData::m_score;

//---------------------
//	コンストラクタ
//---------------------
CScoreData::CScoreData()
{
	Init();
}

//---------------------
//		初期化
//---------------------
void CScoreData::Init()
{
	m_score = 0;
}
