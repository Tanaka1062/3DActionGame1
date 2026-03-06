#pragma once
#include<DxLib.h>
#include "../mapBase.h"

class CSelectMap : public CMapBase
{
private:
public:
	//コンストラクタ
	CSelectMap();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

};

