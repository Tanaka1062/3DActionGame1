#pragma once
#include"../../lib/model/3DObject.h"

class CGoal:public CObject
{
private:
	bool m_isGoal;			//ゴールフラグ
public:
	//コンストラクタ・デストラクタ
	CGoal();
	~CGoal();

	//初期化
	void Init();
	//オブジェクトのロード
	void Load();

	//当たり判定後の処理
	void HitCalc();

};

