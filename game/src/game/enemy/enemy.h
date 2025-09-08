#pragma once
#include "../character/characterBase.h"
#include "../FOV/FOV.h"


//敵のクラス
class CEnemy:public CCharacterBase
{
private:
	CFOV m_FOV;				//視界範囲クラス

public:
	//コンストラクタ・デストラクタ
	CEnemy();
	~CEnemy();

	//初期化
	void Init(VECTOR _pos = {0.0f,0.0f,0.0f});

	//モデルロード
	void Load();

	//毎フレームする処理
	//追いかける相手の座標
	void Step(VECTOR _pos);

	//描写処理
	void Draw();

	//更新処理
	void Update();

	//視界範囲を取得
	CFOV* GetFOV() { return &m_FOV; }

	//視界範囲に当たった処理
	void HitFOV() { m_FOV.HitCalc(); }

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

	//怯み状態処理
	void Stagger();

	//死亡
	void Die();

	//移動処理
	void Move(VECTOR _pos);


};

