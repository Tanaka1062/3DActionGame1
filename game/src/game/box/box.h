#pragma once
#include "../../lib/model/actor.h"

class CBox : public CActor
{
private:
	int m_hp;				//箱の体力
	float m_gravity;		//重力
public:
	//コンストラクタ・デストラクタ
	CBox();
	~CBox();

	//初期化
	void Init();
	//モデルロード
	void Load(int _modelHndl);
	//毎フレームする処理
	void Step();
	//数値の更新
	void Update();

	//体力を減らす
	void SubHp(int _subHp);

	//重力リセット
	void GravityReset() { m_gravity = 0.0f; }

private:
	//重力処理
	void Gravity();

};

