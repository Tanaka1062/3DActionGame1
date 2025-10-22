#include "boxManager.h"

static const int BOX_MAX = 1;

//---------------------------
//		コンストラクタ
//---------------------------
CBoxManager::CBoxManager()
{
}

//---------------------------
//		 デストラクタ
//---------------------------
CBoxManager::~CBoxManager()
{
	Exit();
}

//---------------------------
//		   初期化
//---------------------------
void CBoxManager::Init()
{
	CBox* box = new CBox;

	box->Init();
	box->SetPos(VGet(0.0f,0.0f,0.0f));

	m_box.push_back(box);
}

//---------------------------
//		 モデルロード
//---------------------------
void CBoxManager::Load()
{
	for (auto ite = m_box.begin(); ite != m_box.end(); ite++)
	{
		(*ite)->Load();
	}
}

//---------------------------
//	   毎フレームする処理
//---------------------------
void CBoxManager::Step(CItemManager* _itemManager)
{
	for (auto ite = m_box.begin(); ite != m_box.end();)
	{
		//毎フレームする処理
		(*ite)->Step();

		//箱が壊れていたら消してそこにアイテムを出す
		if ((*ite)->GetActive() == false)
		{
			_itemManager->SpawnItem((*ite)->GetPos());

			//終了処理
			(*ite)->Exit();

			delete (*ite);

			ite = m_box.erase(ite);
		}
		else
		{
			++ite;
		}
	}
}

//---------------------------
//	   毎フレームする処理
//---------------------------
void CBoxManager::Update()
{
	for (auto ite = m_box.begin(); ite != m_box.end(); ite++)
	{
		(*ite)->Update();
	}

}

//---------------------------
//		  モデル描写
//---------------------------
void CBoxManager::Draw()
{
	for (auto ite = m_box.begin(); ite != m_box.end(); ite++)
	{
		(*ite)->Draw();
	}

}

//---------------------------
//		   終了処理
//---------------------------
void CBoxManager::Exit()
{
	for (auto ite = m_box.begin(); ite != m_box.end();)
	{
		(*ite)->Exit();

		delete (*ite);

		ite = m_box.erase(ite);
	}

}

//箱を取得する
CBox* CBoxManager::GetBox(int _num)
{
	//引数より箱の数が少なければnullをかえす
	if (_num > m_box.size())return nullptr;
	//箱の数をカウントする変数
	int count = 0;
	for (auto ite = m_box.begin(); ite != m_box.end();++ite)
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

