#include "itemInventory.h"
#include "../itemShotBase.h"
#include "../../data.h"

//------------------
//	コンストラクタ
//------------------
CItemInventory::CItemInventory()
{
	Init(nullptr);
}

//------------------
//	  初期化
//------------------
void CItemInventory::Init(CPlayerManager* _playerManager)
{

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_useItem[i] = nullptr;
		m_weaponItem[i] = nullptr;


		if (_playerManager == nullptr)
		{
			m_player[i] = nullptr;
		}
		else
		{
			m_player[i] = _playerManager->GetPlayer(i);
		}
	}
}

//------------------
//毎フレームする処理
//------------------
void CItemInventory::Step(CShotManager* _shot)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{

		//アイテムを使用していたらアイテムを使用する
		if (m_player[i]->GetIsItemUse() == true &&
			m_useItem[i] != nullptr)
		{

		}

		//スキルを使用していたらスキルを使用する
		if (m_weaponItem[i] != nullptr)
		{
			m_weaponItem[i]->Use();
		}
	}
}

//------------------
//	  数値の更新
//------------------
void CItemInventory::Update()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		if (m_useItem[i] != nullptr)
		{
			m_player[i]->SetIsItem(true);
		}
		else
		{
			m_player[i]->SetIsItem(false);
		}
	}

}

//------------------
//	  描写処理
//------------------
void CItemInventory::Draw()
{

	if (m_useItem[0] == nullptr)
	{
		DrawFormatString(32, 128, GetColor(255, 0, 0), "何もない");
	}
	else
	{

	}

	if (m_weaponItem[0] == nullptr)
	{
		DrawFormatString(32, 228, GetColor(255, 0, 0), "何もない");
	}
	else
	{
	}

	if (m_useItem[1] == nullptr)
	{
		DrawFormatString(WINDOW_SIZE_X - 128, 128, GetColor(255, 0, 0), "何もない");
	}
	else
	{

	}

	if (m_weaponItem[1] == nullptr)
	{
		DrawFormatString(WINDOW_SIZE_X - 128, 228, GetColor(255, 0, 0), "何もない");
	}
	else
	{
	}


}

//アイテムを設定
CItemBase* CItemInventory::SetItem(CItemBase* _item,CPlayer* _player)
{

	//アドレス保存用
	CItemBase* item = nullptr;

	//プレイヤーのコントローラーの名前を取得
	tagPadName padName = _player->GetPadName();

	//アドレスを渡す
	return item;
}

