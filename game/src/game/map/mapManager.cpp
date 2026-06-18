#include "mapManager.h"
#include "playMap/grassland/grassland.h"
#include "selectMap/selectMap.h"
#include "resultMap/resultMap.h"
#include "titleMap/titleMap.h"
#include "playMap/playMapData.h"
#include "playMap/test/test.h"

using namespace std;

//デストラクタ
CMapManager::~CMapManager()
{
	Exit();
}

//初期化
void CMapManager::Init(tagMapId _mapId)
{

	switch (_mapId)
	{
	case MAP_ID_PLAY_MAP:
		//マップを変更
		ChangePlayMap();
		break;
	case MAP_ID_SELECT:
		m_map = make_unique<CSelectMap>();
		break;
	case MAP_ID_RESULT:
		m_map = make_unique<CResultMap>();
		break;
	case MAP_ID_TITLE:
		m_map = make_unique<CTitleMap>();
		break;
	}
	m_map->Init(static_cast<int>(_mapId));
}

//モデルロード
void CMapManager::Load()
{
	m_map->Load();
}

//毎フレームする処理
void CMapManager::Step()
{
	m_map->Step();
}

//更新処理
void CMapManager::Update()
{
	m_map->Update();
}

//モデルの描写
void CMapManager::Draw()
{
	if (m_map == nullptr)return;

	m_map->Draw();
}

//終了処理
void CMapManager::Exit()
{
	if (m_map == nullptr)return;
	m_map->Exit();

	m_map.reset();
}

//ゲーム本編のマップ切り替え
void CMapManager::ChangePlayMap()
{
	CPlayMapData* mapData = CPlayMapData::GetInstance();
	switch (mapData->GetSelectMap())
	{
	case playMap::MAP_1:
		m_map = make_unique<CGrassland>();
		break;
	case playMap::MAP_2:
		m_map = make_unique<CTest>();
		break;
	}

}

