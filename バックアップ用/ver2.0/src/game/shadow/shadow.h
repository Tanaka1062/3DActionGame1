#pragma once
#include"../../lib/model/3DObject.h"

//丸影のクラス
class CShadow :public CObject
{
private:

public:

	//初期化
	void Init(VECTOR _pos,float _scale);
	//モデルのロード
	void Load();
	//毎フレームする処理
	void Step(VECTOR _pos);

};

