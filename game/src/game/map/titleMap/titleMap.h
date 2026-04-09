#pragma once
#include<DxLib.h>
#include "../mapBase.h"

class CTitleMap : public CMapBase
{
private:
public:
	//コンストラクタ
	CTitleMap();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

};

