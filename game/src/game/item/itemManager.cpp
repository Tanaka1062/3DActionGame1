#include "itemManager.h"
#include "../system/soundManager.h"

using namespace std;

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
	m_coinManager.Init();
}

//-----------------------
//	  モデルロード
//-----------------------
void CItemManager::Load()
{

	m_mapItemManager.Load();
	m_spawnItemManager.Load();
	m_coinManager.Load();

	//マップアイテムを代入
	for (int mapItem_i = 0; mapItem_i < m_mapItemManager.GetItemNum(); mapItem_i++)
	{
		unique_ptr<CItemBase> mapItem = m_mapItemManager.GetItem(mapItem_i);

		m_item.push_back(move(mapItem));
	}

	//マップのコインを代入
	for (int mapCoin_i = 0; mapCoin_i < m_coinManager.GetMapCoinNum(); mapCoin_i++)
	{
		unique_ptr<CItemBase> mapCoin = m_coinManager.GetMapCoin(mapCoin_i);

		m_item.push_back(move(mapCoin));
	}
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CItemManager::Step(CPlayerManager* _playerManager, tagMapCenterId _mapId)
{

	m_mapItemManager.Step();
	m_spawnItemManager.Step();
	m_coinManager.Step();


	//スポーンしたらアイテムを増やす
	if (m_spawnItemManager.GetIsItemSpawn() == true)
	{
		unique_ptr<CItemBase> spawnItem = m_spawnItemManager.SpawnItem(_mapId);
		
		//アイテムが入っていたら生成する
		if (spawnItem != nullptr)
		{
			m_item.push_back(move(spawnItem));
		}
	}

	for (auto item_i = m_item.begin(); item_i != m_item.end(); )
	{
		if ((*item_i)->GetActive() == false &&
			(*item_i)->GetIsSpawn() == true)
		{
			//速度をゼロにする
			(*item_i)->SetSpeed(ZERO);

			if ((*item_i)->GetItemType() != ITEM_TYPE_COIN)
			{
				//消えたアイテムをスポーンアイテムマネージャーに戻す
				m_spawnItemManager.ReturnItem(move(*item_i));
			}
			else
			{
				//消えたコインをコインマネージャーに戻す
				m_coinManager.ReturnCoin(move(*item_i));
			}

			//消えたアイテムをリストから消す
			item_i = m_item.erase(item_i);
		}
		else
		{
			//ここ消したら処理が増えない---------
			(*item_i)->Step();

			++item_i;
			//-----------------------------------

		}
	
	}


	//プレイヤーのコインを落とす処理
	for (int player_i = 0; player_i < _playerManager->GetPlayerNum(); player_i++)
	{
		CPlayer* player = _playerManager->GetPlayer(player_i);

		int dropCoin = player->GetDropCoin();

		for (int dropCoin_i = 0; dropCoin_i < dropCoin; dropCoin_i++)
		{
			CSoundManager::Play(CSoundManager::SE_COINDROP, DX_PLAYTYPE_BACK);

			//コインを生成して保存する
			unique_ptr<CItemBase> dropCoin = m_coinManager.SpawnCoin();
			
			//飛ばす方向を求める
			float rotY = static_cast<float>((GetRand(360)) * (DX_PI_F / 180.0f));

			//コインを飛ばす
			dropCoin->Drop(player->GetCenter(), rotY);

			//飛ばしたコインをアイテムリストに入れる
			m_item.push_back(move(dropCoin));

		}

		//落とすコインの量をゼロに戻す
		player->SetDropCoin(0);
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
	m_coinManager.Exit();

	for (auto item_i = m_item.begin(); item_i != m_item.end(); ++item_i)
	{
		if ((*item_i) != nullptr)
		{
			(*item_i)->Exit();
		}
	}

	//アイテムを全て消す
	m_item.clear();

}

//-----------------------
//アイテムのアドレスを取得
//-----------------------
CItemBase* CItemManager::GetItem(int _num)
{
	int itemNum = 0;

	for (auto item_i = m_item.begin(); item_i != m_item.end(); ++item_i)
	{
		return (*item_i).get();
		if (itemNum == _num)
		{
			return (*item_i).get();
		}
		itemNum++;
	}

	return nullptr;

}

//-----------------------
//	アイテムの呼び出し
//-----------------------
void CItemManager::RequestItem(tagItemName _itemName, VECTOR _requestPos)
{
	//呼び出すアイテムを持ってくる
	unique_ptr<CItemBase> requestItem = m_spawnItemManager.RequestItem(_itemName);

	//アイテムを指定した座標に移動させ出現させる
	requestItem->SetPos(_requestPos);
	requestItem->SetActive(true);

	//呼び出したアイテムをクラスに保存する
	m_item.push_back(move(requestItem));

}

//-----------------------
//	 コインの呼び出し
//-----------------------
void CItemManager::RequestCoin(VECTOR _requestPos)
{
	//呼び出すコインを持ってくる
	unique_ptr<CItemBase> requestCoin = m_coinManager.SpawnCoin();

	//コインを指定した座標に移動させ出現させる
	requestCoin->SetPos(_requestPos);
	requestCoin->SetActive(true);

	//呼び出したコインをクラスに保存する
	m_item.push_back(move(requestCoin));
}

