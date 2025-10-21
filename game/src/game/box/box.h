#pragma once
#include "../../lib/model/3DObject.h"

class CBox : public CObject
{
private:
	int m_hp;

public:
	//コンストラクタ・デストラクタ
	CBox();
	~CBox();

	//初期化
	void Init();
	//モデルロード
	void Load();

	//体力を減らす
	void SubHp(int _subHp);
};

