#include "spawnCoinManager.h"
#include "../../map/map.h"

using namespace std;

constexpr int SPAWN_PROBABILITY_INIT[ITEM_NUM] =					//アイテムの出現確率の初期値
{
	40,
	5,
	5,
	5,
	5,
};

constexpr int SPAWN_PROBABILITY_DECREASE[ITEM_NUM] =				//アイテムの出現確率の減少値
{
	0,
	5,
	5,
	5,
	5,
};

static const char* MODEL_PATH =							//モデルのパス
{
	"data/model/item/powerCoin/coin.mv1",
};

constexpr int MAP_FRAME_NUM = 56;			//マップのフレーム番号

constexpr int SPAWN_TIME = 3 * 60;			//スポーンするまで時間

constexpr int SPAWN_NUM[MAP_CENTER_NUM]		//マップごとのフレームの数
	{
		8,
		8,
		8,
		8,
		11,
	};


//-----------------------
//	  コンストラクタ
//-----------------------
CSpawnCoinManager::CSpawnCoinManager()
{
	m_hndl = -1;

	m_spawnTime = 0;

	m_isItemSpawn = false;
}

//-----------------------
//	  デストラクタ
//-----------------------
CSpawnCoinManager::~CSpawnCoinManager()
{
	Exit();

}

//-----------------------
//		初期化
//-----------------------
void CSpawnCoinManager::Init(CPlayerManager* _playerManager)
{
	//アイテムが増えすぎないようにする
	m_coin.clear();

	//生成用アイテムの生成
	for (int spawn_i = 0; spawn_i < SPAWN_ITEM_MAX * ITEM_NUM; spawn_i++)
	{
		m_coin.push_back(make_unique<CCoin>());
	}

	for (int spawn_i = 0; spawn_i < m_coin.size(); spawn_i++)
	{
		m_coin[spawn_i]->Init();
	}

	m_hndl = -1;
	m_spawnTime = 0;
	m_isItemSpawn = false;

	int spawnNum = 0;
	for (int map_i = 0; map_i < MAP_CENTER_NUM; map_i++)
	{
		m_spawnData.push_back(vector<tagSpawnData>());
		spawnNum = SPAWN_NUM[map_i];

		for (int spawn_i = 0; spawn_i < spawnNum; spawn_i++)
		{
			tagSpawnData spawnData;
			spawnData.isSpawn = false;
			spawnData.pos = ZERO;
			m_spawnData[map_i].push_back(spawnData);
		}
	}

}

//-----------------------
//	  モデルロード
//-----------------------
void CSpawnCoinManager::Load()
{
	//アイテムのモデル読み込み
	m_hndl = MV1LoadModel(MODEL_PATH);

	//アイテムのモデルロード
	for (int spawn_i = 0; spawn_i < m_coin.size(); spawn_i++)
	{
		m_coin[spawn_i]->Load(m_hndl);
	}

	//マップのフレームハンドルをロード
	int mapFrameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_GRASSLAND]);

	//フレームの番号
	int frameNum = MAP_FRAME_NUM;

	//出現位置をアイテムのスポーン情報に入力-------------------------------------	
	for (int map_i = 0; map_i < m_spawnData.size(); map_i++)
	{
		for (int spawn_i = 0; spawn_i < m_spawnData[map_i].size(); spawn_i++)
		{
			//出現座標保存用
			VECTOR spawnPos = ZERO;

			//フレームから出現座標を取得
			spawnPos = MV1GetFramePosition(mapFrameHndl, frameNum);

			//アイテムのスポーン情報に設定
			m_spawnData[map_i][spawn_i].pos = spawnPos;

			//フレームの番号を進める
			frameNum += 2;

		}

	}
	//---------------------------------------------------------------------------
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CSpawnCoinManager::Step()
{
	m_spawnTime++;
	if (m_spawnTime >= SPAWN_TIME)
	{
		m_spawnTime = 0;
		//アイテムを出現させる
		m_isItemSpawn = true;
	}

	int mapSpawnPosNum[MAP_CENTER_NUM] = { 0 };

	//全てのスポーン座標がtrueになったらリセットする
	for (int map_i = 0; map_i < m_spawnData.size(); map_i++)
	{
		for (int spawnPos_i = 0; spawnPos_i < m_spawnData[map_i].size(); spawnPos_i++) 
		{
			//まだ出現していない場所はカウントしない
			if (m_spawnData[map_i][spawnPos_i].isSpawn == false)continue;

			mapSpawnPosNum[map_i]++;
		}
	}

	//すべての座標にアイテムが出現したら全部の出現フラグをfalseにする------------------

	for (int map_i = 0; map_i < m_spawnData.size(); map_i++)
	{
		if (mapSpawnPosNum[map_i] == m_spawnData[map_i].size()) 
		{
			for (int spawn_i = 0; spawn_i < m_spawnData[map_i].size(); spawn_i++)
			{
				m_spawnData[map_i][spawn_i].isSpawn = false;
			}
		}
	}

	//---------------------------------------------------------------------------------
}

//-----------------------
//		終了処理
//-----------------------
void CSpawnCoinManager::Exit()
{
	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		if (m_hndl != -1)
		{
			MV1DeleteModel(m_hndl);
			m_hndl = -1;
		}
	}

	for (int item_i = 0; item_i < m_coin.size();item_i++)
	{
		if (m_coin[item_i] == nullptr)continue;

		m_coin[item_i]->Exit();
	}

	//増えすぎないように消す------
	m_coin.clear();
	m_spawnData.clear();
	//----------------------------
}

//-----------------------
//アイテムのアドレスを取得
//-----------------------
CItemBase* CSpawnCoinManager::GetItem(int _num)
{
	if (m_coin.size() < _num)return nullptr;

	return m_coin[_num].get();

}

//アイテムを出現させる
unique_ptr<CItemBase> CSpawnCoinManager::SpawnItem(tagMapCenterId _mapId)
{

	//どのアイテムをスポーンさせるかを決める----------
	
	//スポーンさせるアイテムの名前
	tagItemName itemNameId = ITEM_NONE;

	//アイテムの出現確率
	int spawnProbability = 0;
	//出現確率の減少量を保存
	int spawnProbabilityDecrease = 0;
	
	//------------------------------------------------

	unique_ptr<CItemBase> spawnItem = nullptr;

	for (int spawn_i = 0; spawn_i < m_coin.size(); spawn_i++)
	{
		//中身が無いアイテムはスキップする
		if (m_coin[spawn_i] == nullptr)continue;

		if (m_coin[spawn_i]->GetItemName() == itemNameId &&
			m_coin[spawn_i]->GetActive() == false)
		{
			spawnItem = move(m_coin[spawn_i]);
			break;
		}
	}

	//もしも用意しているアイテムがなかったら生成する
	if (spawnItem == nullptr)
	{
		spawnItem = make_unique<CCoin>();

		spawnItem->Init();
		spawnItem->Load(m_hndl);

	}

	//アイテムをの生存フラグをtrueにする
	spawnItem->SetActive(true);
	spawnItem->SetIsSpawn(true);

	//スポーンさせる座標を決める---------------------
	int spawnPosId = 0;

	while (true)
	{
		spawnPosId = GetRand(static_cast<int>( m_spawnData[_mapId].size()) - 1);

		if (m_spawnData[_mapId][spawnPosId].isSpawn == false)
		{
			spawnItem->SetPos(m_spawnData[_mapId][spawnPosId].pos);
			m_spawnData[_mapId][spawnPosId].isSpawn = true;
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
unique_ptr<CItemBase> CSpawnCoinManager::SpawnCoin()
{
	//出現させるコインの保存用
	unique_ptr<CItemBase> spawnCoin = nullptr;

	//リストの中からコインを探して保存用に入れる
	for (int spawn_i = 0; spawn_i < m_coin.size(); spawn_i++)
	{
		if (m_coin[spawn_i] == nullptr)continue;

		if (m_coin[spawn_i]->GetItemName() == ITEM_COIN)
		{
			spawnCoin = move(m_coin[spawn_i]);
		}
	}

	//コインのクラスがなかったら新しく作る
	if (spawnCoin == nullptr)
	{
		spawnCoin = make_unique<CCoin>();

		spawnCoin->Init();
		spawnCoin->Load(m_hndl);
	}

	//コインの生存フラグをtrueにする
	spawnCoin->SetActive(true);
	spawnCoin->SetIsSpawn(true);

	//スポーンしたコインを返す
	return spawnCoin;
}

//アイテムを元に戻す
void CSpawnCoinManager::ReturnItem(unique_ptr<CItemBase> _returnItme)
{
	for (int spawn_i = 0; spawn_i < m_coin.size(); spawn_i++)
	{
		if (m_coin[spawn_i] == nullptr)
		{
			m_coin[spawn_i] = move(_returnItme);
			m_coin[spawn_i]->SetActive(false);
			m_coin[spawn_i]->SetIsSpawn(false);
			return;
		}

	}
	//空きが無かったらvectorに入れる
	_returnItme->SetActive(false);
	_returnItme->SetIsSpawn(false);
	m_coin.push_back(move(_returnItme));

}
