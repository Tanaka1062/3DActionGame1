#include "itemManager.h"

//-----------------------
//	  コンストラクタ
//-----------------------
CItemManager::CItemManager()
{

}

//-----------------------
//	  デストラクタ
//-----------------------
CItemManager::~CItemManager()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CItemManager::Init(CPlayerManager* _playerManager)
{
	m_mapItemManager.Init();
	m_spawnItemManager.Init(_playerManager);
}

//-----------------------
//	  モデルロード
//-----------------------
void CItemManager::Load()
{
	m_mapItemManager.Load();
	m_spawnItemManager.Load();

	//マップアイテムを代入
	for (int mapItem_i = 0; mapItem_i < m_mapItemManager.GetItemNum(); mapItem_i++)
	{
		CItemBase* item = m_mapItemManager.GetItem(mapItem_i);
		m_item.push_back(item);
	}
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CItemManager::Step(CPlayerManager* _playerManager)
{
	m_mapItemManager.Step();
	m_spawnItemManager.Step();

	//スポーンしたらアイテムを増やす
	if (m_spawnItemManager.GetIsItemSpawn() == true)
	{
		m_item.push_back(m_spawnItemManager.SpawnItem());
	}

	for (auto item_i = m_item.begin(); item_i != m_item.end(); )
	{
		if ((*item_i)->GetActive() == false &&
			(*item_i)->GetIsSpawn() == true)
		{
			(*item_i)->Exit();

			delete (*item_i);

			item_i = m_item.erase(item_i);
		}
		else
		{
			(*item_i)->Step();

			++item_i;

		}
	
	}

	//プレイヤーのコインを落とす処理
	for (int player_i = 0; player_i < _playerManager->GetPlayerNum(); player_i++)
	{
		CPlayer* player = _playerManager->GetPlayer(player_i);

		int dropCoin = player->GetDropCoin();

		for (int dropCoin_i = 0; dropCoin_i < dropCoin; dropCoin_i++)
		{
			//CCoin* coin = new CCoin;

			//coin->Init();
			//coin->Load();
		}
	}

}

//-----------------------
//		数値の更新
//-----------------------
void CItemManager::Update()
{
	for (auto item_i = m_item.begin(); item_i != m_item.end(); ++item_i)
	{
		(*item_i)->Update();
	}
}

//-----------------------
//	オブジェクトの描写
//-----------------------
void CItemManager::Draw()
{
	for (auto item_i = m_item.begin(); item_i != m_item.end(); ++item_i)
	{
		(*item_i)->Draw();
	}
}

//-----------------------
//		終了処理
//-----------------------
void CItemManager::Exit()
{
	m_mapItemManager.Exit();
	m_spawnItemManager.Exit();

	for (auto item_i = m_item.begin(); item_i != m_item.end();)
	{
		item_i = m_item.erase(item_i);

	}

}

//-----------------------
//アイテムのアドレスを取得
//-----------------------
CItemBase* CItemManager::GetItem(int _num)
{

	int itemNum = 0;

	for (auto item_i = m_item.begin(); item_i != m_item.end(); item_i++)
	{
		if (itemNum == _num)
		{
			return *item_i;
		}
		itemNum++;
	}

	return nullptr;

}
