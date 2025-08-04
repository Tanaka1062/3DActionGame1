#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"

static const char GROUND_MODEL_PATH[] =
{ "data/model/field/field.x" };		//ロードするファイル名


class CGround :public CObject
{
private:

public:
	//コンストラクタ・デストラクタ
	CGround();
	~CGround();


	//初期化
	void Init();



};

