#include "spawnCoinManager.h"
#include "../../map/map.h"
#include "../coin/spawnCoin.h"
#include "../coin/coin.h"

using namespace std;

static const char* MODEL_PATH =							//モデルのパス
{
	"data/model/item/powerCoin/coinTest.mv1",
};

constexpr int MAP_FRAME_NUM = 130;			//マップのフレーム番号

constexpr int SPAWN_ITEM_MAX = 20;		//アイテムの最大量

constexpr int SPAWN_NUM[MAP_CENTER_NUM]		//マップごとのフレームの数
	{
		22,
		6,
		21,
		20,
		9,
	};

//constexpr int SPAWN_NUM[MAP_CENTER_NUM]		//マップごとのフレームの数
//	{
//		22,
//		6,
//		0,
//		0,
//		0,
//	};


//-----------------------
//	  コンストラクタ
//-----------------------
CSpawnCoinManager::CSpawnCoinManager()
{
	m_hndl = -1;
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
void CSpawnCoinManager::Init()
{
	//コインが増えすぎないようにする
	m_mapCoin.clear();
	m_dropCoin.clear();
	
	//マップに出現するコインを生成
	for (int map_i = 0; map_i < MAP_CENTER_NUM; map_i++)
	{
		for (int mapCoin_i = 0; mapCoin_i < SPAWN_NUM[map_i]; mapCoin_i++)
		{
			unique_ptr<CItemBase> mapCoin = make_unique<CSpawnCoin>();

			mapCoin->Init();

			m_mapCoin.push_back(move(mapCoin));
		}
	}

	//ドロップするコインを生成
	for (int dropCoin_i = 0; dropCoin_i < SPAWN_ITEM_MAX; dropCoin_i++)
	{
		unique_ptr<CItemBase> dropCoin = make_unique<CCoin>();

		dropCoin->Init();

		m_dropCoin.push_back(move(dropCoin));
	}

	m_hndl = -1;

}

//-----------------------
//	  モデルロード
//-----------------------
void CSpawnCoinManager::Load()
{
	//アイテムのモデル読み込み
	m_hndl = MV1LoadModel(MODEL_PATH);

	//アイテムのモデルロード
	for (int mapCoin_i = 0; mapCoin_i < m_mapCoin.size(); mapCoin_i++)
	{
		m_mapCoin[mapCoin_i]->Load(m_hndl);
	}
	for (int dropCoin_i = 0; dropCoin_i < m_dropCoin.size(); dropCoin_i++)
	{
		m_dropCoin[dropCoin_i]->Load(m_hndl);
	}

	//マップのフレームハンドルをロード
	int mapFrameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_GRASSLAND]);

	//フレームの番号
	int frameNum = MAP_FRAME_NUM;

	//出現位置をアイテムのスポーン情報に入力-------------------------------------	
	for (int mapCoin_i = 0; mapCoin_i < m_mapCoin.size(); mapCoin_i++)
	{
		//出現座標保存用
		VECTOR spawnPos = ZERO;

		//フレームから出現座標を取得
		spawnPos = MV1GetFramePosition(mapFrameHndl, frameNum);

		//マップのコインに出現座標を設定
		m_mapCoin[mapCoin_i]->SetSpawnPos(spawnPos);

		//フレームの番号を進める
		frameNum += 2;

	}
	//---------------------------------------------------------------------------
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CSpawnCoinManager::Step()
{
}

//-----------------------
//		終了処理
//-----------------------
void CSpawnCoinManager::Exit()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}

	for (int mapCoin_i = 0; mapCoin_i < m_mapCoin.size(); mapCoin_i++)
	{
		if (m_mapCoin[mapCoin_i] == nullptr)continue;

		m_mapCoin[mapCoin_i]->Exit();
	}

	for (int dropCoin_i = 0; dropCoin_i < m_dropCoin.size(); dropCoin_i++)
	{
		if (m_dropCoin[dropCoin_i] == nullptr)continue;

		m_dropCoin[dropCoin_i]->Exit();
	}

	//増えすぎないように消す------
	m_mapCoin.clear();
	m_dropCoin.clear();
	//----------------------------
}

//-----------------------
//マップのコインのアドレスを取得
//-----------------------
unique_ptr<CItemBase> CSpawnCoinManager::GetMapCoin(int _num)
{
	if (m_mapCoin.size() < _num)return nullptr;

	unique_ptr<CItemBase> mapCoin = move(m_mapCoin[_num]);

	return mapCoin;
}

//-----------------------
//	コインを出現させる
//-----------------------
unique_ptr<CItemBase> CSpawnCoinManager::SpawnCoin()
{
	//出現させるコインの保存用
	unique_ptr<CItemBase> spawnCoin = nullptr;

	//リストの中からコインを探して保存用に入れる
	for (int dropCoin_i = 0; dropCoin_i < m_dropCoin.size(); dropCoin_i++)
	{
		if (m_dropCoin[dropCoin_i] == nullptr)continue;

		spawnCoin = move(m_dropCoin[dropCoin_i]);
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
	for (int dropCoin_i = 0; dropCoin_i < m_dropCoin.size(); dropCoin_i++)
	{
		if (m_dropCoin[dropCoin_i] == nullptr)
		{
			m_dropCoin[dropCoin_i] = move(_returnItme);
			m_dropCoin[dropCoin_i]->SetActive(false);
			m_dropCoin[dropCoin_i]->SetIsSpawn(false);
			return;
		}

	}
	//空きが無かったらvectorに入れる
	_returnItme->SetActive(false);
	_returnItme->SetIsSpawn(false);
	m_dropCoin.push_back(move(_returnItme));

}
