#include  "mapItemManager.h"
#include "itemObject/bomb/bomb.h"
#include "itemObject/box/box.h"

using namespace std;

static const char* MODEL_PATH =				//モデルのパス
{
	"data/model/item/box/box.mv1",
};

static const char FRAME_PATH[] =
{ "data/model/map/TestMap6Frame.mv1" };		//ロードするファイル名

constexpr int SPAWN_POS_FRAME_ID[MAP_ITEM_SPAWN_POS_NUM] =	//スポーンする座標のフレームID
{
	23,
	25,
	27,
	29,
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
	int mapFrameHndl = MV1LoadModel(FRAME_PATH);

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
