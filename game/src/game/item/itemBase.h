#pragma once

#include "../../lib/model/3DObject.h"
#include "../data.h"
#include "../shot/shotManager.h"
#include "../player/player.h"

//アイテムのベースクラス
class CItemBase :public CObject
{
protected:
	tagItemName m_name;		//アイテムの名前

	//アイテムのタイプ
	enum tagType
	{
		TYPE_NONE = -1,		//何もないタイプ
		TYPE_SHOT,			//弾発射タイプ
		TYPE_USE,			//使用タイプ
	};

	tagType m_type;			//アイテムのタイプ

public:
	//コンストラクタ
	CItemBase();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();

	//使用した時の処理
	virtual void Use();


	//アイテムの名前を設定
	void SetName(tagItemName _name) { m_name = _name; }
	//アイテムの名前を取得
	tagItemName GetName() { return m_name; }

};


