#include "spawnItemManager.h"
#include "itemObject/bomb/bomb.h"
#include "itemObject/box/box.h"
#include "weapon/sword/sword.h"
#include "weapon/gun/gun.h"
#include"weapon/ax/ax.h"

using namespace std;

constexpr int SPAWN_PROBABILITY_INIT[ITEM_NUM] =					//アイテムの出現確率の初期値
{
	30,
	5,
	5,
	5,
	5,
};

constexpr int SPAWN_PROBABILITY_DECREASE[ITEM_NUM] =				//アイテムの出現確率の減少値
{
	2,
	5,
	5,
	5,
	5,
};

static const char* MODEL_PATH[ITEM_NUM] =							//モデルのパス
{
	"data/model/item/powerCoin/coin.mv1",
	"data/model/item/bomb/bomb.mv1",
	"data/model/item/weapon/sword/sword.mv1",
	"data/model/item/weapon/gun/gun.mv1",
	"data/model/item/weapon/ax/ax.mv1",

};

static const char FRAME_PATH[] =
"data/model/map/TestMap6Frame.mv1";			//ロードするファイル名


constexpr int SPAWN_TIME = 7 * 60;		//スポーンするまで時間

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

		m_isSpawnPos[spawnPos_i] = false;
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
	//アイテムが増えすぎないようにする
	m_item.clear();

	//アイテムの出現確率を全て消す
	m_spawnProbability.clear();

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
		else if (spawn_i <= SPAWN_ITEM_MAX * (ITEM_SWORD + 1))
		{
			m_item.push_back(make_unique<CSword>());
		}
		else if (spawn_i <= SPAWN_ITEM_MAX * (ITEM_GUN)+1)
		{
			m_item.push_back(make_unique<CGun>());
		}
		else if (spawn_i <= SPAWN_ITEM_MAX * (ITEM_AX)+1)
		{
			m_item.push_back(make_unique<CAx>());
		}
	}

	for (int item_i = 0; item_i < ITEM_NUM; item_i++)
	{
		m_spawnProbability.push_back(SPAWN_PROBABILITY_INIT[item_i]);
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
	//アイテムのモデル読み込み
	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		if (m_hndl[hndl_i] == -1)
		{
			m_hndl[hndl_i] = MV1LoadModel(MODEL_PATH[hndl_i]);
		}
	}

	//アイテムのモデルロード
	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		int hndl = m_hndl[m_item[spawn_i]->GetItemName()];

		m_item[spawn_i]->Load(hndl);
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

	//すべての座標にアイテムが出現したら全部の出現フラグをfalseにする
	if (spawnPosNum == ITEM_SPAWN_POS_NUM)
	{
		for (int spawnPos_i = 0; spawnPos_i < ITEM_SPAWN_POS_NUM; spawnPos_i++)
		{
			m_isSpawnPos[spawnPos_i] = false;
		}
	}
	

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

	for (int item_i = 0; item_i < m_item.size();item_i++)
	{
		if (m_item[item_i] == nullptr)continue;

		m_item[item_i]->Exit();
	}

	//deleteの代わりでアイテムが増えすぎないようにする
	m_item.clear();
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
	
	//スポーンさせるアイテムの名前
	tagItemName itemNameId = ITEM_NONE;

	//アイテムの出現確率の合計を求める
	int spawnProbabilitySum = 0;
	for (int item_i = 0; item_i < m_spawnProbability.size(); item_i++)
	{
		spawnProbabilitySum += m_spawnProbability[item_i];
	}

	//確率の合計を最大値としてランダムな値を取得する
	int randNum = GetRand(spawnProbabilitySum);

	//スポーンするアイテムを作成

	//アイテムの出現確率
	int spawnProbability = 0;
	//出現確率の減少量を保存
	int spawnProbabilityDecrease = 0;

	for (int item_i = 0; item_i < ITEM_NUM; item_i++)
	{
		//アイテムの出現確率を求める
		spawnProbability += m_spawnProbability[item_i];

		//出現確率に入ったら出現するアイテムを特定する
		if (randNum <= spawnProbability)
		{
			itemNameId = static_cast<tagItemName>(item_i);

			//出現確率がマイナスになる場合は0になるまでの減少量を保存する
			if (m_spawnProbability[item_i] - SPAWN_PROBABILITY_DECREASE[item_i] > 0)
			{
				m_spawnProbability[item_i] -= SPAWN_PROBABILITY_DECREASE[item_i];
				spawnProbabilityDecrease = SPAWN_PROBABILITY_DECREASE[item_i];
			}
			//出現確率の減少量を保存する
			else
			{
				spawnProbabilityDecrease = m_spawnProbability[item_i];
				m_spawnProbability[item_i] = 0;
			}
			break;
		}
	}

	//出現確率の最低値保存用
	int minSpawnProbability = -1;
	//一番低い出現確率のアイテム
	tagItemName minSpawnProbabilityItem = ITEM_NONE;

	//一番出現確率が低いアイテムを調べる
	for (int item_i = 0; item_i < m_spawnProbability.size(); item_i++)
	{
		//今回出現したアイテムはスキップする
		if (item_i == itemNameId)continue;

		//出現確率が現在の値より低かったら値を保存する
		if (minSpawnProbability > m_spawnProbability[item_i] || minSpawnProbability == -1)
		{
			minSpawnProbabilityItem = static_cast<tagItemName>(item_i);
			minSpawnProbability = m_spawnProbability[item_i];
		}

	}

	//一番出現確率が低いアイテムの出現確率を減少量分上げる
	m_spawnProbability[minSpawnProbabilityItem] += spawnProbabilityDecrease;
	
	//------------------------------------------------

	unique_ptr<CItemBase> spawnItem = nullptr;

	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		//中身が無いアイテムはスキップする
		if (m_item[spawn_i] == nullptr)continue;

		if (m_item[spawn_i]->GetItemName() == itemNameId &&
			m_item[spawn_i]->GetActive() == false)
		{
			spawnItem = move(m_item[spawn_i]);
			break;
		}
	}

	//もしも用意しているアイテムがなかったら生成する
	if (spawnItem == nullptr)
	{
		switch (itemNameId)
		{
		case ITEM_COIN:
			spawnItem = make_unique<CCoin>();
			break;
		case ITEM_BOMB:
			spawnItem = make_unique<CBomb>();
			break;
		case ITEM_SWORD:
			spawnItem = make_unique<CSword>();
			break;
		case ITEM_GUN:
			spawnItem = make_unique<CGun>();
			break;
		case ITEM_AX:
			spawnItem = make_unique<CAx>();
			break;
		}

		spawnItem->Init();
		spawnItem->Load(m_hndl[itemNameId]);

	}

	//アイテムをの生存フラグをtrueにする
	spawnItem->SetActive(true);
	spawnItem->SetIsSpawn(true);

	//スポーンさせる座標を決める---------------------
	int spawnPosId = 0;

	while (true)
	{
		spawnPosId = GetRand(ITEM_SPAWN_POS_NUM - 1);

		if (m_isSpawnPos[spawnPosId] == false)
		{
			spawnItem->SetPos(m_spawnPos[spawnPosId]);
			m_isSpawnPos[spawnPosId] = true;
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

//コインを出現させる
unique_ptr<CItemBase> CSpawnItemManager::SpawnCoin()
{
	//出現させるコインの保存用
	unique_ptr<CItemBase> spawnCoin = nullptr;

	//リストの中からコインを探して保存用に入れる
	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		if (m_item[spawn_i] == nullptr)continue;

		if (m_item[spawn_i]->GetItemName() == ITEM_COIN)
		{
			spawnCoin = move(m_item[spawn_i]);
		}
	}

	//コインのクラスがなかったら新しく作る
	if (spawnCoin == nullptr)
	{
		spawnCoin = make_unique<CCoin>();

		spawnCoin->Init();
		spawnCoin->Load(m_hndl[ITEM_COIN]);
	}

	//コインの生存フラグをtrueにする
	spawnCoin->SetActive(true);
	spawnCoin->SetIsSpawn(true);

	//スポーンしたコインを返す
	return spawnCoin;
}

//アイテムを元に戻す
void CSpawnItemManager::ReturnItem(unique_ptr<CItemBase> _returnItme)
{
	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		if (m_item[spawn_i] == nullptr)
		{
			m_item[spawn_i] = move(_returnItme);
			m_item[spawn_i]->SetActive(false);
			m_item[spawn_i]->SetIsSpawn(false);
			return;
		}

	}
	//空きが無かったらvectorに入れる
	_returnItme->SetActive(false);
	_returnItme->SetIsSpawn(false);
	m_item.push_back(move(_returnItme));

}
