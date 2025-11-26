#include  "mapItemManager.h"
#include "itemObject/bomb/bomb.h"
#include "itemObject/box/box.h"


static const char* MODEL_PATH =				//モデルのパス
{
	"data/model/item/box/box.mv1",
};

static const char FRAME_PATH[] =
{ "data/model/map/TestMap6Frame.mv1" };		//ロードするファイル名


//-----------------------
//	  コンストラクタ
//-----------------------
CMapItemManager::CMapItemManager()
{

	for (int item_i = 0; item_i < MAP_ITEM_SPAWN_POS_NUM; item_i++)
	{
		m_item[item_i] = nullptr;
	}

	m_hndl = -1;

}

//-----------------------
//	  デストラクタ
//-----------------------
CMapItemManager::~CMapItemManager()
{
	Exit();

	for (int item_i = 0; item_i < MAP_ITEM_SPAWN_POS_NUM; item_i++)
	{
		delete m_item[item_i];

		m_item[item_i] = nullptr;

	}

}

//-----------------------
//		初期化
//-----------------------
void CMapItemManager::Init()
{
	//アイテムの初期化
	for (int item_i = 0; item_i < MAP_ITEM_SPAWN_POS_NUM; item_i++)
	{
		m_item[item_i] = new CBox;

		m_item[item_i]->Init();
	}

	m_hndl = -1;

}

//-----------------------
//	  モデルロード
//-----------------------
void CMapItemManager::Load()
{

	m_hndl = MV1LoadModel(MODEL_PATH);

	for (int item_i = 0; item_i < MAP_ITEM_SPAWN_POS_NUM; item_i++)
	{
		m_item[item_i]->Load(m_hndl);
	}

	//マップのフレームハンドルをロード
	int mapFrameHndl = MV1LoadModel(FRAME_PATH);

	for (int spawnPos_i = 0; spawnPos_i < MAP_ITEM_SPAWN_POS_NUM; spawnPos_i++)
	{
		//アイテムの出現座標を保存
		VECTOR spawnPos = ZERO;

		switch (spawnPos_i)
		{
		case MAP_ITEM_SPAWN_POS_1:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 23);
			break;
		case MAP_ITEM_SPAWN_POS_2:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 25);
			break;
		case MAP_ITEM_SPAWN_POS_3:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 27);
			break;
		case MAP_ITEM_SPAWN_POS_4:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 29);
			break;
		}

		m_item[spawnPos_i]->SetSpawnPos(spawnPos);
	}

}

//-----------------------
//	毎フレームする処理
//-----------------------
void CMapItemManager::Step()
{
	for (int item_i = 0; item_i < MAP_ITEM_SPAWN_POS_NUM; item_i++)
	{
		m_item[item_i]->Step();
	}
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

	for (int item_i = 0; item_i < MAP_ITEM_SPAWN_POS_NUM;item_i++)
	{
		if (m_item == nullptr)continue;

		m_item[item_i]->Exit();

	}

}

