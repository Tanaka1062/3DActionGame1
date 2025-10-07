#pragma once
#include "../character/characterBase.h"
#include "../FOV/FOV.h"
#include <iostream>
#include <vector>

using namespace std;

//敵のクラス
class CEnemyBase :public CCharacterBase
{
private:
	CFOV m_FOV;				//視界範囲クラス
	int m_rootHndl;			//ルート用のモデルハンドル
	int m_rootId;			//今の自分の目的地
	float m_moveSpeed;		//速度
	vector<int>m_root;		//ルート

public:
	//コンストラクタ・デストラクタ
	CEnemyBase();
	~CEnemyBase();

	//初期化
	virtual void Init();

	//モデルロード
	virtual void Load(int _rootHndl,int _modelHndl);

	//毎フレームする処理
	//追いかける相手の座標
	virtual void Step(VECTOR _pos);

	//描写処理
	virtual void Draw();

	//更新処理
	virtual void Update();

	//視界範囲を取得
	CFOV* GetFOV() { return &m_FOV; }

	//視界範囲に当たった処理
	void HitFOV() { m_FOV.HitCalc(); }

	//ルートを設定
	void SetRoot(int _root);

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

	//追いかける移動処理
	void MoveChase(VECTOR _pos);

	//ルートを移動処理
	void MoveRoot();
};

