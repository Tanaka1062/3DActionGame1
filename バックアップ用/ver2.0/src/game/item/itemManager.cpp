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

	//スポーンアイテムを代入
	for (int spawnItem_i = 0; spawnItem_i < m_spawnItemManager.GetItemNum(); spawnItem_i++)
	{
		CItemBase* item = m_spawnItemManager.GetItem(spawnItem_i);

		m_item.push_back(item);
	}
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CItemManager::Step()
{
	m_mapItemManager.Step();
	m_spawnItemManager.Step();

	for (auto item_i = m_item.begin(); item_i != m_item.end(); ++item_i)
	{

		(*item_i)->Step();

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
	if (m_item.size() < _num)return nullptr;

	return m_item[_num];

	//アイテムの数をカウントする変数
	//int count = 0;
	//for (auto ite = m_item.begin(); ite != m_item.end(); ++ite)
	//{
	//	//引数の数字と同じならアドレスを返す
	//	if (count == _num)
	//	{
	//		return *ite;
	//	}
	//	count++;

	//}
	//return nullptr;

}

//-----------------------
//コインのアドレスを取得
//-----------------------
CPowerCoin* CItemManager::GetCoin(int _num)
{
	return m_spawnItemManager.GetCoin(_num);
}


