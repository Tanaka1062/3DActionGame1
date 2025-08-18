#pragma once
#include "../character/characterBase.h"
#include "../attack/attack.h"
#include "../FOV/FOV.h"

static const int PLAYER_NUM = 1;	//プレイヤーの数

//敵のクラス
class CEnemy:public CCharacterBase
{
private:
	CAttack m_attack;		//攻撃クラス
	CFOV m_FOV;				//視界範囲クラス

public:
	//コンストラクタ・デストラクタ
	CEnemy();
	~CEnemy();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

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

