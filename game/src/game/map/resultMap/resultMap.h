#pragma once
#include<DxLib.h>
#include "../mapBase.h"

class CResultMap : public CMapBase
{
private:
public:
	//コンストラクタ
	CResultMap();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

};

