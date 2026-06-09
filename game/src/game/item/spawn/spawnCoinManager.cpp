#include "spawnCoinManager.h"
#include "../coin/spawnCoin.h"
#include "../coin/dropCoin.h"

using namespace std;

static const char* MODEL_PATH =				//モデルのパス
{
	"data/model/item/coin/coin.mv1",
};

constexpr int MAP_FRAME_NUM = 130;			//マップのフレーム番号

constexpr int DROP_COIN_MAX = 100;			//コインの最大量

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
	
	//ドロップするコインを生成
	for (int dropCoin_i = 0; dropCoin_i < DROP_COIN_MAX; dropCoin_i++)
	{
		unique_ptr<CItemBase> dropCoin = make_unique<CDropCoin>();

		dropCoin->Init();

		m_dropCoin.push_back(move(dropCoin));
	}

	m_hndl = -1;

}

//-----------------------
//	  モデルロード
//-----------------------
void CSpawnCoinManager::Load(CMapBase* _map)
{
	for (int stage_i = 0; stage_i < _map->GetStageNum(); stage_i++)
	{
		//ステージの情報を取得
		int stageHndl = _map->GetHndl(stage_i);
		CMapBase::tagStageSpawnData stageSpawnData = _map->GetStageSpawnData(stage_i);
		int frameNum = stageSpawnData.coinFrameNum;
		int spawnNum = stageSpawnData.coinSpawnNum;

		//出現するコインを生成--------------------------------------------------------	
		for (int mapCoin_i = 0; mapCoin_i < spawnNum; mapCoin_i++)
		{
			//出現座標取得
			VECTOR spawnPos = MV1GetFramePosition(stageHndl, frameNum);

			//コインを生成
			unique_ptr<CItemBase> mapCoin = make_unique<CSpawnCoin>();
			mapCoin->Init();
			mapCoin->SetPos(spawnPos);
			mapCoin->SetSpawnPos(spawnPos);
			m_mapCoin.push_back(move(mapCoin));

			//フレームの番号を進める
			frameNum += 2;

		}
		//---------------------------------------------------------------------------
	}

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
		if (m_dropCoin[dropCoin_i] != nullptr)
		{
			spawnCoin = move(m_dropCoin[dropCoin_i]);
			break;
		}
	}

	//コインのクラスがなかったら新しく作る
	if (spawnCoin == nullptr)
	{
		spawnCoin = make_unique<CDropCoin>();

		spawnCoin->Init();
		spawnCoin->Load(m_hndl);
	}

	//コインの生存フラグをtrueにする
	spawnCoin->SetActive(true);

	//スポーンしたコインを返す
	return spawnCoin;
}

//アイテムを元に戻す
void CSpawnCoinManager::ReturnCoin(unique_ptr<CItemBase> _returnItme)
{
	//マップのコインを戻す
	if (_returnItme->GetIsSpawn() == false)
	{
		for (int mapCoin_i = 0; mapCoin_i < m_mapCoin.size(); mapCoin_i++)
		{
			if (m_mapCoin[mapCoin_i] == nullptr) 
			{
				m_mapCoin[mapCoin_i] = move(_returnItme);
				m_mapCoin[mapCoin_i]->SetActive(false);
				return;
			}
		}
		//空きが無かったら新しく作り入れる
		_returnItme->SetActive(false);
		m_mapCoin.push_back(move(_returnItme));
	}
	//ドロップのコインを戻す
	else
	{
		for (int dropCoin_i = 0; dropCoin_i < m_dropCoin.size(); dropCoin_i++)
		{
			if (m_dropCoin[dropCoin_i] == nullptr)
			{
				m_dropCoin[dropCoin_i] = move(_returnItme);
				m_dropCoin[dropCoin_i]->SetActive(false);
				return;
			}
		}
		//空きが無かったら新しく作り入れる
		_returnItme->SetActive(false);
		m_dropCoin.push_back(move(_returnItme));
	}


}

