#include "itemManager.h"
#include "fireRing/fireRing.h"
#include "harbAmulent/harbAmulent.h"

//-----------------------
//	  コンストラクタ
//-----------------------
CItemManager::CItemManager()
{
	m_shot = nullptr;
	m_player = nullptr;

	for (int i = 0; i < ITEM_NUM; i++)
	{
		m_hndl[i] = -1;
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
void CItemManager::Init(CPlayer* _player, CShotManager* _shot)
{
	//アドレスを保存
	m_player = _player;
	m_shot = _shot;

	//モデルハンドルを初期化
	for (int i = 0; i < ITEM_NUM; i++)
	{
		m_hndl[i] = -1;
	}

	if (m_item.size() == ITEM_NUM)return;

	//アイテムクラスを生成し初期化
	for (int i = 0; i < ITEM_NUM; i++)
	{
		CItemBase* item = nullptr;

		//アイテムの名前を設定
		switch (i)
		{
		case 0:
			item = new CFireRing;
			item->Init(m_player);
			m_item.push_back(item);
			break;
		case 1:
			item = new CHarbAmulent;
			item->Init(m_player);
			m_item.push_back(item);
			break;
		}

	}

	int num = 0;
	
	int rootHndl = MV1LoadModel("data/model/map/map1FramePos.mv1");

	for (auto ite = m_item.begin(); ite != m_item.end(); ++ite)
	{
		VECTOR start = VGet(0.0f, 0.0f, 0.0f);

		switch (num)
		{
		case 0:
			start = MV1GetFramePosition(rootHndl,18);
			break;
		case 1:
			start = MV1GetFramePosition(rootHndl,20);
			break;
		}

		(*ite)->SetPos(start);

		num++;
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

//-----------------------
//アイテムのアドレスを取得
//-----------------------
CItemBase* CItemManager::GetItem(int _num)
{
	//引数よりアイテムの数がすくなければnullを返す
	if (_num > m_item.size())return nullptr;
	//アイテムの数をカウントする変数
	int count = 0;
	for (auto ite = m_item.begin(); ite != m_item.end(); ++ite)
	{
		//引数の数字と同じならアドレスを返す
		if (count == _num)
		{
			return *ite;
		}
		count++;

	}
	return nullptr;

}

//-----------------------
//	   アイテムを設定
//-----------------------
void CItemManager::SetItem(int _num,CItemBase* _item)
{
	//アイテムの数をカウントする変数
	int count = 0;
	for (auto ite = m_item.begin(); ite != m_item.end();++ite)
	{
		//引数の数字と同じならアイテムを入れ替える
		if (count == _num)
		{
			//入れ替えるアイテムがnullptrなら消す
			if (_item == nullptr)
			{
				ite = m_item.erase(ite);
			}
			else
			{
				*ite = _item;
				//プレイヤーの位置に座標を設定
				(*ite)->SetPos(m_player->GetPos());
			}
			return;
		}
		count++;

	}

}

//-----------------------
// アイテムを出現させる
//-----------------------
void CItemManager::SpawnItem(VECTOR _pos, tagItemName _name)
{
	//名前の保存用
	tagItemName name = _name;

	//アイテムの保存用
	CItemBase* item = nullptr;

	//アイテムが何もない場合ランダムなアイテムが選ばれる
	if (name == ITEM_NONE)
	{
		//アイテムの名前を設定
		name = static_cast<tagItemName>(GetRand(ITEM_NUM -1));
	}

	//アイテム事に設定をする
	switch (name)
	{
	case ITEM_FIRE_RING:
		item = new CFireRing;
		break;
	case ITEM_HARB_AMULENT:
		item = new CHarbAmulent;
		break;
	}

	item->Init(m_player);
	item->DuplicateModel(m_hndl[item->GetName()]);
	item->SetPos(_pos);
	m_item.push_back(item);

}

