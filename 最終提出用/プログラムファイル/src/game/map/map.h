#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"



class CMap :public CObject
{
private:
	int m_hitHndl;		//当たり判定ようのマップのハンドル
public:
	//コンストラクタ・デストラクタ
	CMap();
	~CMap();


	//初期化
	void Init();

	//モデルロード
	void Load();

	//モデル描写
	void Draw();

	//当たり判定ようのマップのハンドルを取得
	int GetHitHndl() { return m_hitHndl; }
};

