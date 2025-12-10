#include "spawnItemManager.h"
#include "itemObject/bomb/bomb.h"
#include "itemObject/box/box.h"


static const char* MODEL_PATH[ITEM_NUM] =				//モデルのパス
{
	"data/model/item/powerCoin/coin.mv1",
	"data/model/item/bomb/bomb.mv1",
};

static const char FRAME_PATH[] =
{ "data/model/map/TestMap6Frame.mv1" };			//ロードするファイル名


static const int SPAWN_TIME = 7 * 60;		//スポーンするまで時間

//-----------------------
//	  コンストラクタ
//-----------------------
CSpawnItemManager::CSpawnItemManager()
{
	

	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		m_hndl[hndl_i] = -1;
	}

	m_spawnTime = 0;

	m_isItemSpawn = false;
	for (int spawnPos_i = 0; spawnPos_i < ITEM_SPAWN_POS_NUM; spawnPos_i++)
	{
		m_spawnPos[spawnPos_i] = ZERO;
	}

}

//-----------------------
//	  デストラクタ
//-----------------------
CSpawnItemManager::~CSpawnItemManager()
{
	Exit();

}

//-----------------------
//		初期化
//-----------------------
void CSpawnItemManager::Init(CPlayerManager* _playerManager)
{
	//生成用アイテムの生成
	for (int spawn_i = 0; spawn_i < SPAWN_ITEM_MAX * ITEM_NUM; spawn_i++)
	{

		if (spawn_i <= SPAWN_ITEM_MAX * (ITEM_COIN + 1))
		{
			m_item.push_back(make_unique<CCoin>());
		}
		else if (spawn_i <= SPAWN_ITEM_MAX * (ITEM_BOMB + 1))
		{
			m_item.push_back(make_unique<CBomb>());
		}
	}

	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		m_item[spawn_i]->Init();
	}


	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		m_hndl[hndl_i] = -1;
	}

	m_spawnTime = 0;

	m_isItemSpawn = false;

	for (int spawnPos_i = 0; spawnPos_i < ITEM_SPAWN_POS_NUM; spawnPos_i++)
	{
		m_spawnPos[spawnPos_i] = ZERO;

		m_isSpawnPos[spawnPos_i] = false;
	}

}

//-----------------------
//	  モデルロード
//-----------------------
void CSpawnItemManager::Load()
{

	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		if (m_hndl[hndl_i] == -1)
		{
			m_hndl[hndl_i] = MV1LoadModel(MODEL_PATH[hndl_i]);
		}
	}

	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		int hndl = m_hndl[m_item[spawn_i]->GetItemName()];

		m_item[spawn_i]->Load(hndl);
	}

	//for (int item_i = 0; item_i < m_item.size(); item_i++)
	//{
	//	//m_item[item_i]->Load(m_hndl[item_i]);
	//}

	for (int item_i = 0; item_i < SPAWN_ITEM_MAX * ITEM_NUM; item_i++)
	{
		CItemBase* item =  m_item[item_i].get();
	}

	//マップのフレームハンドルをロード
	int mapFrameHndl = MV1LoadModel(FRAME_PATH);

	for (int spawnPos_i = 0; spawnPos_i < ITEM_SPAWN_POS_NUM; spawnPos_i++)
	{
		//アイテムの出現座標を保存
		VECTOR spawnPos = ZERO;

		switch (spawnPos_i)
		{
		case ITEM_SPAWN_POS_1:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 7);
			break;
		case ITEM_SPAWN_POS_2:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 9);
			break;
		case ITEM_SPAWN_POS_3:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 11);
			break;
		case ITEM_SPAWN_POS_4:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 13);
			break;
		case ITEM_SPAWN_POS_5:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 15);
			break;
		case ITEM_SPAWN_POS_6:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 17);
			break;
		case ITEM_SPAWN_POS_7:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 19);
			break;
		case ITEM_SPAWN_POS_8:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 21);
			break;

		}

		spawnPos.y += 10.0f;

		m_spawnPos[spawnPos_i] = spawnPos;

		m_isSpawnPos[spawnPos_i] = false;
	}

}

//-----------------------
//	毎フレームする処理
//-----------------------
void CSpawnItemManager::Step()
{
	m_spawnTime++;
	if (m_spawnTime >= SPAWN_TIME)
	{
		m_spawnTime = 0;
		//アイテムを出現させる
		m_isItemSpawn = true;
	}

	int spawnPosNum = 0;

	//全てのスポーン座標がtrueになったらリセットする
	for (int spawnPos_i = 0; spawnPos_i < ITEM_SPAWN_POS_NUM; spawnPos_i++)
	{
		if (m_isSpawnPos[spawnPos_i] == true)
			spawnPosNum++;
	}

	if (spawnPosNum == ITEM_SPAWN_POS_NUM)
	{
		for (int spawnPos_i = 0; spawnPos_i < ITEM_SPAWN_POS_NUM; spawnPos_i++)
		{
			m_isSpawnPos[spawnPos_i] = false;
		}
	}

	//コインをドロップしていたら落とす
	//for (int player_i = 0; player_i < m_playerManager->GetPlayerNum(); player_i++)
	//{
	//	CPlayer* player = m_playerManager->GetPlayer(player_i);

	//	if (player->GetDropCoin() >= 1)
	//	{
	//		for (auto coin_i = m_item.begin(); coin_i != m_item.end(); coin_i++)
	//		{

	//			if ((*coin_i)->GetItemType() != ITEM_TYPE_COIN)continue;

	//			CCoin* coin = nullptr;

	//			coin = dynamic_cast<CCoin*>((*coin_i));

	//			//プレイヤーの持っているコインがある場合落とす
	//			if (coin->GetPlayerName() == player->GetPlayerName())
	//			{

	//				float radian = static_cast<float>((GetRand(60) - 30) * (DX_PI_F / 180.0f));

	//				//とりあえず中心に飛ばす
	//				float rotY = atan2f(-player->GetPos().x, -player->GetPos().z);

	//				rotY += radian;

	//				coin->Drop(player->GetCenter(), rotY);
	//				break;
	//			}
	//		}
	//		//一ずつ減らす
	//		player->SetDropCoin(player->GetDropCoin() - 1);
	//	}
	//}

}

//-----------------------
//		終了処理
//-----------------------
void CSpawnItemManager::Exit()
{
	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		if (m_hndl[hndl_i] != -1)
		{
			MV1DeleteModel(m_hndl[hndl_i]);
			m_hndl[hndl_i] = -1;
		}
	}

	for (auto item_i = m_item.begin(); item_i != m_item.end();)
	{
		(*item_i)->Exit();

		item_i = m_item.erase(item_i);

	}

}

//-----------------------
//アイテムのアドレスを取得
//-----------------------
CItemBase* CSpawnItemManager::GetItem(int _num)
{
	if (m_item.size() < _num)return nullptr;

	return m_item[_num].get();

}

//アイテムを出現させる
unique_ptr<CItemBase> CSpawnItemManager::SpawnItem()
{

	//どのアイテムをスポーンさせるかを決める----------
	
	int randNum = GetRand(100);

	tagItemName itemNameId = ITEM_NONE;

	//スポーンするアイテムを作成

	if (randNum < 80)
	{
		itemNameId = ITEM_COIN;
	}
	else if (randNum < 100)
	{
		itemNameId = ITEM_BOMB;
	}
	
	//------------------------------------------------

	unique_ptr<CItemBase> spawnItem = nullptr;

	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		if (m_item[spawn_i]->GetItemName() == itemNameId &&
			m_item[spawn_i]->GetActive() == false)
		{
			spawnItem = m_item[spawn_i].get();
			spawnItem->SetActive(true);
			spawnItem->SetIsSpawn(true);
			break;
		}
	}

	//スポーンさせる座標を決める---------------------
	int spawnPosId = 0;

	while (true)
	{
		spawnPosId = GetRand(ITEM_SPAWN_POS_NUM - 1);

		if (m_isSpawnPos[spawnPosId] == false)
		{
			spawnItem->SetPos(m_spawnPos[spawnPosId]);
			m_isItemSpawn = true;
			break;
		}
	}

	//-----------------------------------------------



	//スポーンしているかをリセット
	m_isItemSpawn = false;

	//スポーンしたアイテムを返す
	return spawnItem;
}

//アイテムを元に戻す
void CSpawnItemManager::ReturnItem(unique_ptr<CItemBase> _returnItme)
{
	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		if (m_item[spawn_i] == nullptr)
		{
			m_item[spawn_i] = move(_returnItme);
			return;
		}
	}
}
