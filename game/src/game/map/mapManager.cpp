#include "mapManager.h"
#include "playMap/grassland/grassland.h"
#include "selectMap/selectMap.h"
#include "resultMap/resultMap.h"
#include "titleMap/titleMap.h"

//コンストラクタ・デストラクタ
CMapManager::CMapManager()
{
	m_map = nullptr;
}

CMapManager::~CMapManager()
{
	Exit();
}

//初期化
void CMapManager::Init(tagMapId _mapId)
{
	switch (_mapId)
	{
	case MAP_ID_GRASSLAND:
		m_map = new CGrassland;
		break;
	case MAP_ID_SELECT:
		m_map = new CSelectMap;
		break;
	case MAP_ID_RESULT:
		m_map = new CResultMap;
		break;
	case MAP_ID_TITLE:
		m_map = new CTitleMap;
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

	delete m_map;
	m_map = nullptr;
}

