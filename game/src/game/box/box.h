#pragma once
#include "../../lib/model/3DObject.h"

class CBox : public CObject
{
private:

public:
	//コンストラクタ・デストラクタ
	CBox();
	~CBox();

	//初期化
	void Init();
	//モデルロード
	void Load();

};

