#include  "mapItemManager.h"
#include "../itemObject/bomb/bomb.h"
#include "../itemObject/box/box.h"

using namespace std;

static const char* MODEL_PATH =				//モデルのパス
{
	"data/model/item/box/box.mv1",
};

//-----------------------
//	  コンストラクタ
//-----------------------
CMapItemManager::CMapItemManager()
{
	m_hndl = -1;
}

//-----------------------
//	  デストラクタ
//-----------------------
CMapItemManager::~CMapItemManager()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CMapItemManager::Init()
{
	//アイテムが増えすぎないようにする
	m_item.clear();

	m_hndl = -1;

}

//-----------------------
//	  モデルロード
//-----------------------
void CMapItemManager::Load(CMapBase* _map)
{

	m_hndl = MV1LoadModel(MODEL_PATH);

	//アイテムをステージに必要な数だけ生成
	for (int stage_i = 0; stage_i < _map->GetStageNum(); stage_i++)
	{
		//ステージの情報を取得
		int stageHndl = _map->GetHndl(stage_i);
		CMapBase::tagStageSpawnData stageSpawnData = _map->GetStageSpawnData(stage_i);
		int frameNum = stageSpawnData.mapItemFrameNum;
		int spawnNum = stageSpawnData.mapItemSpawnNum;

		for (int spawnPos_i = 0; spawnPos_i < spawnNum; spawnPos_i++)
		{
			//アイテムの出現座標を保存
			VECTOR spawnPos = V_ZERO;
			spawnPos = MV1GetFramePosition(stageHndl, frameNum);
			frameNum += 2;

			//アイテムを生成して出現座標を設定する
			unique_ptr<CItemBase> box = make_unique<CBox>();
			box->Init();
			box->SetPos(spawnPos);
			box->SetSpawnPos(spawnPos);
			m_item.push_back(move(box));
		}
	}

	//アイテムのモデルロード
	for (int item_i = 0; item_i < m_item.size(); item_i++)
	{
		m_item[item_i]->Load(m_hndl);
	}
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CMapItemManager::Step()
{
}

//-----------------------
//		終了処理
//-----------------------
void CMapItemManager::Exit()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}

	//deleteの代わり
	m_item.clear();
}

//アイテムのアドレスを取得
unique_ptr<CItemBase> CMapItemManager::GetItem(int _num)
{
	if (m_item.size() <= _num)return nullptr;

	unique_ptr<CItemBase> item = move(m_item[_num]);

	return item;
}

