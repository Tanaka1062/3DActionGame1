#pragma once
#include "../../lib/model/3DObject.h"

class CBox : public CObject
{
private:
	int m_hp;
	VECTOR m_size;
public:
	//コンストラクタ・デストラクタ
	CBox();
	~CBox();

	//初期化
	void Init();
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();

	//体力を減らす
	void SubHp(int _subHp);
};

