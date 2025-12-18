#pragma once
#include"../../lib/model/3DObject.h"


class CSky:public CObject
{
private:

public:
	//コンストラクタ・デストラクタ
	CSky();
	~CSky();


	//初期化
	void Init();

	//画像ロード
	void Load();

	//毎フレームする処理
	void Step();

private:

	//回転
	void Rotate();

};

