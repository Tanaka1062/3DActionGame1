#pragma once
#include<DxLib.h>
#include "../../mapBase.h"

class CGrassland :public CMapBase
{
private:
public:
	//コンストラクタ
	CGrassland();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

};

