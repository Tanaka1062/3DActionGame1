#pragma once
#include "../../lib/model/3DObject.h"

class CBox : public CObject
{
private:
	int m_hp;				//箱の体力
	VECTOR m_size;			//当たり判定用の箱のサイズ
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

	//中心座標を取得
	VECTOR GetCenter();

	//体力を減らす
	void SubHp(int _subHp);

	//当たり判定ようの箱のサイズを取得
	VECTOR GetSize() { return m_size; }


};

