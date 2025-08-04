#pragma once
#include<DxLib.h>
#include"../../lib/model/3DObject.h"

static const char SKY_MODEL_PATH[] =
{ "data/model/sky/sky.mv1" };	//ロードするファイル名

class CSky:public CObject
{
private:

public:
	//コンストラクタ・デストラクタ
	CSky();
	~CSky();


	//初期化
	void Init();
	//毎フレームする処理
	void Step();

private:

	//回転
	void Rotate();

};

