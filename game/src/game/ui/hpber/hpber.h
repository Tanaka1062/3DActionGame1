#pragma once
#include "../../lib/2DUi/2DUi.h"
#include "../../player/player.h"

//体力バー
class CHpber :public C2DUi
{
private:
	CPlayer* m_player;		//プレイヤーのクラス保存用

public:
	//コンストラクタ・デストラクタ
	CHpber();
	~CHpber();

	//初期化
	void Init(VECTOR _pos = { 0.0f,0.0f,0.0f }, float _rot = 0.0f);
	//毎フレームする処理
	void Step();
	//描写
	void Draw(float _size = 1.0f);

	//プレイヤーのクラスを設定
	void SetPlayer(CPlayer* _player) { m_player = _player; }
};

