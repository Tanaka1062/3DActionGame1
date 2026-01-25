#pragma once
#include "../../../lib/model/3DObject.h"

class CMoveBlock :public CObject
{
private:

public:
	//コンストラクタ・デストラクタ
	CMoveBlock();
	~CMoveBlock();

	//初期化
	void Init();
	
	//モデルロード
	void Load(const char* _filePath);

	//毎フレームする処理
	void Step();
};

