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
		m_skillItem[i] = nullptr;


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
			switch (m_useItem[i]->GetType())
			{
			case ITEM_TYPE_USE:
				m_useItem[i]->Use();
				break;
			case ITEM_TYPE_SHOT:
				CItemShotBase* shotItem = dynamic_cast<CItemShotBase*>(m_useItem[i]);
				shotItem->Use(_shot);
				break;
			}

			//アイテムの使用回数がなくなっていたら消す
			if (m_useItem[i]->GetUseCount() <= 0)
			{
				m_useItem[i]->Exit();

				delete m_useItem[i];

				m_useItem[i] = nullptr;
			}
		}

		//スキルを使用していたらスキルを使用する
		if (m_skillItem[i] != nullptr)
		{
			m_skillItem[i]->Use();
		}
	}
}

//------------------
//	  数値の更新
//------------------
void CItemInventory::Update()
{

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
		switch (m_useItem[0]->GetName())
		{
		case ITEM_FIRE_RING:
			DrawFormatString(32, 128, GetColor(255, 0, 0), "ファイアリング\n%d回使える", m_useItem[0]->GetUseCount());
			break;
		case ITEM_HARB_AMULENT:
			DrawFormatString(32, 128, GetColor(255, 0, 0), "薬草のお守り\n%d回使える", m_useItem[0]->GetUseCount());
			break;
		}

	}

	if (m_skillItem[0] == nullptr)
	{
		DrawFormatString(32, 228, GetColor(255, 0, 0), "何もない");
	}
	else
	{
		switch (m_skillItem[0]->GetName())
		{
		case ITEM_HARB_AMULENT:
			DrawFormatString(32, 228, GetColor(255, 0, 0), "回転切りができる", m_skillItem[0]->GetUseCount());
			break;
		}
	}

	if (m_useItem[1] == nullptr)
	{
		DrawFormatString(WINDOW_SIZE_X - 128, 128, GetColor(255, 0, 0), "何もない");
	}
	else
	{
		switch (m_useItem[1]->GetName())
		{
		case ITEM_FIRE_RING:
			DrawFormatString(WINDOW_SIZE_X - 128, 128, GetColor(255, 0, 0), "ファイアリング\n%d回使える", m_useItem[1]->GetUseCount());
			break;
		case ITEM_HARB_AMULENT:
			DrawFormatString(WINDOW_SIZE_X - 128, 128, GetColor(255, 0, 0), "薬草のお守り\n%d回使える", m_useItem[1]->GetUseCount());
			break;
		}

	}

	if (m_skillItem[1] == nullptr)
	{
		DrawFormatString(WINDOW_SIZE_X - 128, 228, GetColor(255, 0, 0), "何もない");
	}
	else
	{
		switch (m_skillItem[1]->GetName())
		{
		case ITEM_HARB_AMULENT:
			DrawFormatString(WINDOW_SIZE_X - 128, 228, GetColor(255, 0, 0), "回転切りができる", m_useItem[1]->GetUseCount());
			break;
		}
	}


}

//アイテムを設定
CItemBase* CItemInventory::SetItem(CItemBase* _item,CPlayer* _player)
{

	//アドレス保存用
	CItemBase* item = nullptr;

	//プレイヤーのコントローラーの名前を取得
	tagPadName padName = _player->GetPadName();

	//スキルアイテムの交換
	if (_item->GetType() == ITEM_TYPE_SKILL)
	{
		//すでにアイテムが入っている場合交換する
		if (m_skillItem[padName] != nullptr)
		{
			//今のアイテムのアドレスを保存
			item = m_skillItem[padName];
		}

		//インベントリにアイテムのアドレスを取得
		m_skillItem[padName] = _item;

		//プレイヤーのアドレスを設定
		m_skillItem[padName]->SetPlayerClass(_player);

	}
	//使用するアイテムの交換
	else
	{
		//すでにアイテムが入っている場合交換する
		if (m_useItem[padName] != nullptr)
		{
			//今のアイテムのアドレスを保存
			item = m_useItem[padName];
		}

		//インベントリにアイテムのアドレスを取得
		m_useItem[padName] = _item;

		//プレイヤーのアドレスを設定
		m_useItem[padName]->SetPlayerClass(_player);
	}

	//アドレスを渡す
	return item;
}

