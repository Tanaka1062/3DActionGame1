#pragma once

#include "../../lib/model/3DObject.h"
#include "../player/player.h"
#include "../shadow/shadow.h"

//アイテムのベースクラス
class CItemBase :public CObject
{
protected:
	CPlayer* m_player;		//プレイヤーのアドレス保存用
	CShadow m_shadow;		//丸影のクラス

public:
	//コンストラクタ
	CItemBase();

	//初期化
	virtual void Init(CPlayer* _player = nullptr);

	//モデルのロード(一つのモデルしか使わない)
	virtual void Load(const char* _modelPath);

	//モデルのロード(同じモデルを複数使う場合)
	virtual void Load(int _hndl);

	//毎フレームする処理
	virtual void Step();

	//数値の更新
	virtual void Update();

	//モデルの描写
	virtual void Draw();

	//終了処理
	virtual void Exit();

	//使用した時の処理
	virtual void Use();

	//当たった時の処理
	virtual void HitCalc();

	//プレイヤーのクラスを設定
	void SetPlayerClass(CPlayer* _player) { m_player = _player; }

	//丸影の座標を設定
	void SetShadowPos(VECTOR _pos) { m_shadow.SetPos(_pos); }

};


