#include "itemManager.h"
#include "fireRing/fireRing.h"
#include "harbAmulent/harbAmulent.h"
#include "itemObject/bomb/bomb.h"
#include "powerCoin/powerCoin.h"


static const char* MODEL_PATH[ITEM_NUM] =				//モデルのパス
{
	"data/model/item/powerCoin/powerCoinRed.mv1",
	"data/model/item/powerCoin/powerCoinGreen.mv1",
	"data/model/item/powerCoin/powerCoinBlue.mv1" ,
	"data/model/item/bomb/bomb.mv1",
};

static const char FRAME_PATH[] =
{ "data/model/map/TestMap6Frame.mv1" };			//ロードするファイル名


static const int SPAWN_TIME = 10 * 60;		//スポーンするまで時間

//-----------------------
//	  コンストラクタ
//-----------------------
CItemManager::CItemManager()
{
	//アイテムの生成
	for (int item_i = 0; item_i < ITEM_NUM; item_i++)
	{
		CItemBase* item = nullptr;

		switch (item_i)
		{
		case ITEM_COIN_RED:
		case ITEM_COIN_GREEN:
		case ITEM_COIN_BLUE:
			item = new CPowerCoin;
			break;
		case ITEM_BOMB:
			item = new CBomb;
			break;
		}

		m_item.push_back(item);
	}

	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		m_hndl[hndl_i] = -1;
	}

	m_spawnTime = 0;

	for (int spawnPos_i = 0; spawnPos_i < ITEM_SPAWN_POS_NUM; spawnPos_i++)
	{
		m_spawnPos[spawnPos_i] = ZERO;
	}
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
void CItemManager::Init()
{
	for (int item_i = 0; item_i < m_item.size(); item_i++)
	{
		m_item[item_i]->Init();
	}

	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		m_hndl[hndl_i] = -1;
	}

	m_spawnTime = 0;

	for (int spawnPos_i = 0; spawnPos_i < ITEM_SPAWN_POS_NUM; spawnPos_i++)
	{
		m_spawnPos[spawnPos_i] = ZERO;
	}
}

//-----------------------
//	  モデルロード
//-----------------------
void CItemManager::Load()
{

	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		if (m_hndl[hndl_i] == -1)
		{
			m_hndl[hndl_i] = MV1LoadModel(MODEL_PATH[hndl_i]);
		}
	}

	for (int item_i = 0; item_i < m_item.size(); item_i++)
	{
		m_item[item_i]->Load(m_hndl[item_i]);
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
			spawnPos = MV1GetFramePosition(mapFrameHndl, 11);
			break;
		case ITEM_SPAWN_POS_2:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 13);
			break;
		case ITEM_SPAWN_POS_3:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 15);
			break;
		case ITEM_SPAWN_POS_4:
			spawnPos = MV1GetFramePosition(mapFrameHndl, 17);
			break;

		}

		m_spawnPos[spawnPos_i] = spawnPos;
	}

}

//-----------------------
//	毎フレームする処理
//-----------------------
void CItemManager::Step()
{
	for (auto item_i = m_item.begin(); item_i != m_item.end(); ++item_i)
	{

		if ((*item_i)->GetActive() == false)continue;

		(*item_i)->Step();

	}

	m_spawnTime++;
	if (m_spawnTime >= SPAWN_TIME)
	{
		m_spawnTime = 0;
		//アイテムを出現させる
		SpawnItem();
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

		delete (*item_i);

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
//	   アイテムを設定
//-----------------------
void CItemManager::SetItem(int _num,CItemBase* _item,CPlayer* _player)
{
	////アイテムの数をカウントする変数
	//int count = 0;
	//for (auto ite = m_item.begin(); ite != m_item.end();++ite)
	//{
	//	//引数の数字と同じならアイテムを入れ替える
	//	if (count == _num)
	//	{
	//		//入れ替えるアイテムがnullptrなら消す
	//		if (_item == nullptr)
	//		{
	//			ite = m_item.erase(ite);
	//		}
	//		else
	//		{
	//			*ite = _item;
	//			//プレイヤーの位置に座標を設定
	//			(*ite)->SetPos(_player->GetPos());
	//		}
	//		return;
	//	}
	//	count++;

	//}

}

//アイテムを出現させる
void CItemManager::SpawnItem()
{
	//スポーンしていないアイテム
	int itemNum = 0;

	for (int item_i = 0; item_i < m_item.size(); item_i++)
	{
		if (m_item[item_i]->GetActive() == false)
		{
			itemNum++;
		}
	}

	int itemNameId = GetRand(itemNum - 1);

	itemNum = 0;

	for (int item_i = 0; item_i < m_item.size(); item_i++)
	{
		if (m_item[item_i]->GetActive() == false)
		{
			if (item_i == itemNameId)
			{
				//スポーン位置を設定
				int spawnPosId = GetRand(ITEM_SPAWN_POS_NUM - 1);

				m_item[item_i]->SetPos(m_spawnPos[spawnPosId]);
				m_item[item_i]->SetActive(true);
				return;
			}

			itemNum++;
		}
	}


	//ランダムな変数保存用
	//int itemNameId = GetRand(ITEM_NUM - 1);

	////アイテムの出現
	//CItemBase* item = nullptr;

	//switch (itemNameId)
	//{
	//case ITEM_BOMB:
	//	item = new CBomb;
	//	break;
	//}

	//if (item == nullptr)return;

	//item->Init();

	//item->Load(MODEL_PATH[itemNameId]);

	////スポーン位置を設定
	//int spawnPosId = GetRand(ITEM_SPAWN_POS_NUM - 1);

	//item->SetPos(m_spawnPos[spawnPosId]);

	//m_item.push_back(item);
}

