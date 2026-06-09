#include "spawnItemManager.h"
#include "../itemObject/bomb/bomb.h"
#include "../itemObject/box/box.h"
#include "../weapon/hammer/hammer.h"
#include"../weapon/ax/ax.h"
#include "../../system/effectData/effectData.h"
#include "../../../lib/effekseer/effekseer.h"

using namespace std;

constexpr int SPAWN_PROBABILITY_INIT[ITEM_NUM] =					//アイテムの出現確率の初期値
{
	5,
	5,
	5,
};

constexpr int SPAWN_PROBABILITY_DECREASE[ITEM_NUM] =				//アイテムの出現確率の減少値
{
	5,
	5,
	5,
};

static const char* MODEL_PATH[ITEM_NUM] =							//モデルのパス
{
	"data/model/item/bomb/bomb.mv1",
	"data/model/item/weapon/hammer/hammer.mv1",
	"data/model/item/weapon/ax/ax.mv1",

};

constexpr int MAP_FRAME_NUM = 56;			//マップのフレーム番号

constexpr int SPAWN_TIME = 10 * 60;			//スポーンするまで時間

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
		if (spawn_i <= SPAWN_ITEM_MAX * (ITEM_BOMB + 1))
		{
			m_item.push_back(make_unique<CBomb>());
		}
		else if (spawn_i <= SPAWN_ITEM_MAX * (ITEM_HAMMER + 1))
		{
			m_item.push_back(make_unique<CHammer>());
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

}

//-----------------------
//	  モデルロード
//-----------------------
void CSpawnItemManager::Load(CMapBase* _map)
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

	for (int stage_i = 0; stage_i < _map->GetStageNum(); stage_i++)
	{
		//ステージの情報を取得
		int stageHndl = _map->GetHndl(stage_i);
		CMapBase::tagStageSpawnData stageSpawnData = _map->GetStageSpawnData(stage_i);
		int frameNum = stageSpawnData.itemFrameNum;
		int spawnNum = stageSpawnData.itemSpawnNum;

		m_spawnData.push_back(vector<tagSpawnData>());

		for (int spawn_i = 0; spawn_i < spawnNum; spawn_i++)
		{
			//スポーンデータを生成
			tagSpawnData spawnData;
			spawnData.isSpawn = false;
			spawnData.pos = MV1GetFramePosition(stageHndl,frameNum);
			m_spawnData[stage_i].push_back(spawnData);

			//フレーム番号を進める
			frameNum += 2;
		}
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

	//全てのスポーン座標がtrueになったらリセットする
	for (int map_i = 0; map_i < m_spawnData.size(); map_i++)
	{
		int spawnNum = 0;

		for (int spawnPos_i = 0; spawnPos_i < m_spawnData[map_i].size(); spawnPos_i++) 
		{
			//まだ出現していない場所はカウントしない
			if (m_spawnData[map_i][spawnPos_i].isSpawn == false)continue;

			spawnNum++;
		}

		//すべての座標にアイテムが出現したら全部の出現フラグをfalseにする------------------
		if (spawnNum == m_spawnData[map_i].size())
		{
			for (int spawn_i = 0; spawn_i < m_spawnData[map_i].size(); spawn_i++)
			{
				m_spawnData[map_i][spawn_i].isSpawn = false;
			}
		}
		//---------------------------------------------------------------------------------
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

	//増えすぎないように消す------
	m_item.clear();
	m_spawnData.clear();
	//----------------------------
}

//アイテムを出現させる
unique_ptr<CItemBase> CSpawnItemManager::SpawnItem(int _stageId)
{
	//マップにアイテム出現場所がない場合nullptrを返す
	if (m_spawnData[_stageId].size() == 0)
	{
		//スポーンしているかをリセット
		m_isItemSpawn = false;

		return nullptr;
	}

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
		case ITEM_BOMB:
			spawnItem = make_unique<CBomb>();
			break;
		case ITEM_HAMMER:
			spawnItem = make_unique<CHammer>();
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

	//スポーンさせる座標を決める---------------------
	int spawnPosId = 0;

	while (true)
	{
		spawnPosId = GetRand(static_cast<int>( m_spawnData[_stageId].size()) - 1);

		if (m_spawnData[_stageId][spawnPosId].isSpawn == false)
		{
			spawnItem->SetPos(m_spawnData[_stageId][spawnPosId].pos);
			m_spawnData[_stageId][spawnPosId].isSpawn = true;
			m_isItemSpawn = true;
			break;
		}
	}

	//-----------------------------------------------
	//アイテムが出現するエフェクトのID
	int effectId = CEffectData::GetId(EFFECT_SPAWNITEM);

	//エフェクトを呼び出す
	CEffekseerCtrl::Request(effectId, m_spawnData[_stageId][spawnPosId].pos, false);

	//スポーンしているかをリセット
	m_isItemSpawn = false;

	//スポーンしたアイテムを返す
	return spawnItem;
}

//指定したアイテムを呼び出す
unique_ptr<CItemBase> CSpawnItemManager::RequestItem(tagItemName _itemName)
{
	unique_ptr<CItemBase> spawnItem = nullptr;

	for (int spawn_i = 0; spawn_i < m_item.size(); spawn_i++)
	{
		//中身が無いアイテムはスキップする
		if (m_item[spawn_i] == nullptr)continue;

		if (m_item[spawn_i]->GetItemName() == _itemName &&
			m_item[spawn_i]->GetActive() == false)
		{
			spawnItem = move(m_item[spawn_i]);
			break;
		}
	}

	//もしも用意しているアイテムがなかったら生成する
	if (spawnItem == nullptr)
	{
		switch (_itemName)
		{
		case ITEM_BOMB:
			spawnItem = make_unique<CBomb>();
			break;
		case ITEM_HAMMER:
			spawnItem = make_unique<CHammer>();
			break;
		case ITEM_AX:
			spawnItem = make_unique<CAx>();
			break;
		}

		spawnItem->Init();
		spawnItem->Load(m_hndl[_itemName]);

	}

	//アイテムをの生存フラグをtrueにする
	spawnItem->SetActive(true);

	//アイテムを返す
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
			m_item[spawn_i]->SetActive(false);
			return;
		}

	}
	//空きが無かったらvectorに入れる
	_returnItme->SetActive(false);
	m_item.push_back(move(_returnItme));

}

