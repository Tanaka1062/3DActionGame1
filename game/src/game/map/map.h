#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"



class CGround :public CObject
{
private:

public:
	//コンストラクタ・デストラクタ
	CGround();
	~CGround();


	//初期化
	void Init();

	//モデルロード
	void Load();

	//モデル描写
	void Draw();

};

