#pragma once

#include "../../lib/model/3DObject.h"
#include "../data.h"
#include "../player/player.h"

//アイテムのベースクラス
class CItemBase :public CObject
{
protected:
	int m_useCount;			//アイテムの使用回数
	tagItemName m_name;		//アイテムの名前
	tagItemType m_type;		//アイテムのタイプ
	CPlayer* m_player;		//プレイヤーのアドレス保存用

public:
	//コンストラクタ
	CItemBase();

	//初期化
	virtual void Init(CPlayer* _player = nullptr);

	//毎フレームする処理
	virtual void Step();

	//使用した時の処理
	virtual void Use();

	//アイテムの名前を設定
	void SetName(tagItemName _name) { m_name = _name; }
	//アイテムの名前を取得
	tagItemName GetName() { return m_name; }
	//アイテムのタイプを取得
	tagItemType GetType() { return m_type; }

	//アイテムの使用回数を取得
	int GetUseCount() { return m_useCount; }

};


