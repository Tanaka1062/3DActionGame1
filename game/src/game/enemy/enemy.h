#pragma once
#include "../character/characterBase.h"
#include "../attack/attack.h"
#include "../FOV/FOV.h"


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
	//追いかける相手の座標
	void Step(VECTOR _pos);

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
	void Move(VECTOR _pos);

	//視界範囲を取得
	CFOV& GetFOV() { return m_FOV; }

	//視界範囲に当たった処理
	void HitFOV() { m_FOV.HitCalc(); }

};

