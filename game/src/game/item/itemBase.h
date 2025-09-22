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
	CShotManager* m_shot;	//弾のマネージャークラスのアドレス保存用
	CPlayer* m_player;		//プレイヤークラスのアドレス保存用

public:
	//コンストラクタ
	CItemBase();

	//初期化
	virtual void Init(CShotManager* _shot,CPlayer* _player);

	//毎フレームする処理
	virtual void Step();

	//使用した時の処理
	virtual void Use();


	//アイテムの名前を設定
	void SetName(tagItemName _name) { m_name = _name; }
	//アイテムの名前を取得
	tagItemName GetName() { return m_name; }

	//弾のマネージャークラスのアドレスを取得
	void SetShot(CShotManager* _shot) { m_shot = _shot; }

	//プレイヤークラスのアドレスを取得
	void SetPlayer(CPlayer* _player) { m_player = _player; }

};


