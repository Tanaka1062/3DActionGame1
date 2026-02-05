#include  "mapItemManager.h"
#include "itemObject/bomb/bomb.h"
#include "itemObject/box/box.h"
#include "../map/map.h"

using namespace std;

static const char* MODEL_PATH =				//モデルのパス
{
	"data/model/item/box/box.mv1",
};

constexpr int MAP_FRAME_NUM = 89;				//スポーンする座標のフレームID

constexpr int SPAWN_NUM[MAP_CENTER_NUM]		//マップごとのフレームの数
{
	4,
	4,
	4,
	4,
	4,
};

//-----------------------
//	  コンストラクタ
//-----------------------
CMapItemManager::CMapItemManager()
{
	m_hndl = -1;
}

//-----------------------
//	  デストラクタ
//-----------------------
CMapItemManager::~CMapItemManager()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CMapItemManager::Init()
{
	//アイテムが増えすぎないようにする
	m_item.clear();

	//アイテムの初期化
	for (int map_i = 0; map_i < MAP_CENTER_NUM; map_i++)
	{
		for (int item_i = 0; item_i < SPAWN_NUM[map_i]; item_i++)
		{
			unique_ptr<CItemBase> box = make_unique<CBox>();

			box->Init();

			m_item.push_back(move(box));
		}
	}

	m_hndl = -1;

}

//-----------------------
//	  モデルロード
//-----------------------
void CMapItemManager::Load()
{

	m_hndl = MV1LoadModel(MODEL_PATH);

	for (int item_i = 0; item_i < m_item.size(); item_i++)
	{
		m_item[item_i]->Load(m_hndl);
	}

	//マップのフレームハンドルをロード
	int mapFrameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_GRASSLAND]);

	int mapFrameNum = MAP_FRAME_NUM;
	for (int spawnPos_i = 0; spawnPos_i < m_item.size(); spawnPos_i++)
	{
		//アイテムの出現座標を保存
		VECTOR spawnPos = ZERO;

		spawnPos = MV1GetFramePosition(mapFrameHndl, mapFrameNum);
		mapFrameNum += 2;

		m_item[spawnPos_i]->SetSpawnPos(spawnPos);
	}

}

//-----------------------
//	毎フレームする処理
//-----------------------
void CMapItemManager::Step()
{
}

//-----------------------
//		終了処理
//-----------------------
void CMapItemManager::Exit()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}

	//deleteの代わり
	m_item.clear();
}

//アイテムのアドレスを取得
unique_ptr<CItemBase> CMapItemManager::GetItem(int _num)
{
	if (m_item.size() <= _num)return nullptr;

	unique_ptr<CItemBase> item = move(m_item[_num]);

	return item;
}

