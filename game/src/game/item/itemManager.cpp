#include "itemManager.h"


//-----------------------
//	  コンストラクタ
//-----------------------
CItemManager::CItemManager()
{
	Init(nullptr,nullptr);
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
void CItemManager::Init(CShotManager* _shot, CPlayer* _player)
{
	//モデルハンドルを初期化
	for (int i = 0; i < ITEM_NUM; i++)
	{
		m_hndl[i] = -1;
	}

	//アイテムクラスを生成し初期化
	for (int i = 0; i < ITEM_NUM; i++)
	{
		CItemBase* item = new CItemBase;
		item->Init(_shot,_player);
		//座標を設定
		item->SetPos(VGet((float)(i*20.0f),0.0f,0.0f));
		//アイテムの名前を設定
		switch (i)
		{
		case 0:
			item->SetName(ITEM_FIRE_RING);
			break;
		case 1:
			item->SetName(ITME_HARB_AMULENT);
			break;
		}
		m_item.push_back(item);
	}

}

//-----------------------
//	  モデルロード
//-----------------------
void CItemManager::Load()
{
	//アイテムのモデルのパスを管理======
	const char* MODEL_PATH[ITEM_NUM] =
	{
		"data/model/item/fireRing.mv1",
		"data/model/item/harbAmulent.mv1",
	};
	//==================================

	//モデルのハンドルを設定
	for (int i = 0; i < ITEM_NUM; i++)
	{
		m_hndl[i] = MV1LoadModel(MODEL_PATH[i]);
	}

	//モデルをロード
	for (auto ite = m_item.begin(); ite != m_item.end();++ite)
	{
		(*ite)->DuplicateModel(m_hndl[(*ite)->GetName()]);
	}

}

//-----------------------
//	毎フレームする処理
//-----------------------
void CItemManager::Step()
{
	//アイテムの処理
	for (auto ite = m_item.begin(); ite != m_item.end(); ++ite)
	{
		(*ite)->Step();
	}
}

//-----------------------
//		数値の更新
//-----------------------
void CItemManager::Update()
{
	//アイテムの更新
	for (auto ite = m_item.begin(); ite != m_item.end(); ++ite)
	{
		(*ite)->Update();
	}
}

//-----------------------
//	オブジェクトの描写
//-----------------------
void CItemManager::Draw()
{
	//アイテムの描写
	for (auto ite = m_item.begin(); ite != m_item.end(); ++ite)
	{
		(*ite)->Draw();
	}
}

//-----------------------
//		終了処理
//-----------------------
void CItemManager::Exit()
{
	//アイテムの終了処理
	for (auto ite = m_item.begin(); ite != m_item.end();)
	{
		(*ite)->Exit();

		delete (*ite);

		//終了処理が終わったアイテムを消す
		ite = m_item.erase(ite);

	}
}
