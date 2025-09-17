#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"



class CMap :public CObject
{
private:

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

};

