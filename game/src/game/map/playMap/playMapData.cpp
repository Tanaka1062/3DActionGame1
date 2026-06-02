#include "playMapData.h"

CPlayMapData* CPlayMapData::m_instance = nullptr;

CPlayMapData::CPlayMapData()
{
	Init();
}

//‰Šú‰»
void CPlayMapData::Init()
{
	m_selectMap = playMap::MAP_1;
}

