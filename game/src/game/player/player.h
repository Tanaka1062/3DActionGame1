#pragma once
#include "../character/characterBase.h"
#include "../attack/attack.h"

static const int PLAYER_NUM = 1;	//プレイヤーの数

class CPlayer:public CCharacterBase
{
private:
	CAttack m_attack;		//攻撃クラス

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step(float _rotY);

	//描写処理
	void Draw();

private:
	//待機状態処理
	void Wait();

	//歩く状態処理
	void Walk();

	//ジャンプ状態処理
	void Jump();

	//攻撃状態処理
	void Attack();

	//怯み状態処理
	void Stagger();

	//移動処理
	void Move(float _rotY);

};

