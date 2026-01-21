#include  "mapItemManager.h"
#include "itemObject/bomb/bomb.h"
#include "itemObject/box/box.h"
#include "../map/map.h"

using namespace std;

static const char* MODEL_PATH =				//モデルのパス
{
	"data/model/item/box/box.mv1",
};

constexpr int SPAWN_POS_FRAME_ID[MAP_ITEM_SPAWN_POS_NUM] =	//スポーンする座標のフレームID
{
	59,
	61,
	63,
	65,
	67,
	69,
	71,
	73,
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
	m_item.reserve(MAP_ITEM_SPAWN_POS_NUM);

	//アイテムの初期化
	for (int item_i = 0; item_i < MAP_ITEM_SPAWN_POS_NUM; item_i++)
	{
		unique_ptr<CItemBase> box = make_unique<CBox>();

		box->Init();

		m_item.push_back(move(box));
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

	for (int spawnPos_i = 0; spawnPos_i < MAP_ITEM_SPAWN_POS_NUM; spawnPos_i++)
	{
		//アイテムの出現座標を保存
		VECTOR spawnPos = ZERO;

		spawnPos = MV1GetFramePosition(mapFrameHndl, SPAWN_POS_FRAME_ID[spawnPos_i]);

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
