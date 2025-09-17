#pragma once
#include "../character/characterBase.h"
#include "../shot/shotManager.h"

static const int PLAYER_NUM = 1;	//プレイヤーの数

//プレイヤークラス
class CPlayer:public CCharacterBase
{
private:

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//初期化
	void Init(CShotManager* _shot);

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step(float _rotY);

	//描写処理
	void Draw();

	//更新処理
	void Update();


private:
	//待機状態処理
	void Wait();

	//歩く状態処理
	void Walk();

	//ジャンプ状態処理
	void Jump();

	//攻撃前処理
	void AttackIn();

	//攻撃状態処理
	void Attack();

	//攻撃後処理
	void AttackOut();

	//アイテム使用前
	void ItemUseIn();

	//アイテム使用中
	void ItemUse();

	//アイテム使用後
	void ItemUseOut();

	//怯み状態処理
	void Stagger();

	//死亡
	void Die();

	//移動処理
	void Move(float _rotY);

	//アイテム処理
	void Item();

	//重力処理
	void Gravity();

};

