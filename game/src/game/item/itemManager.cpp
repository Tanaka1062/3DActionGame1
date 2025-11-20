#include "itemManager.h"
#include "fireRing/fireRing.h"
#include "harbAmulent/harbAmulent.h"

static const char* MODEL_PATH[ITEM_NUM] =				//モデルのパス
{
	"data/model/item/bomb/bomb.mv1",
};

//-----------------------
//	  コンストラクタ
//-----------------------
CItemManager::CItemManager()
{
	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		m_hndl[hndl_i] = -1;
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
	for (int hndl_i = 0; hndl_i < ITEM_NUM; hndl_i++)
	{
		m_hndl[hndl_i] = -1;
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

}

//-----------------------
//	毎フレームする処理
//-----------------------
void CItemManager::Step()
{
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

//-----------------------
// アイテムを出現させる
//-----------------------
void CItemManager::SpawnItem(VECTOR _pos)
{
	////名前の保存用

	////アイテムの保存用
	//CItemBase* item = nullptr;

	////アイテムが何もない場合ランダムなアイテムが選ばれる

	////アイテム事に設定をする

	//item->Init();
	//item->Load();
	//item->SetPos(_pos);
	//m_item.push_back(item);

}

