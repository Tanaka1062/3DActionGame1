#pragma once
#include "../../lib/model/3DObject.h"
#include <vector>
#include <iostream>


class C3DUi :public CObject
{
private:
	std::vector<int>m_materialHndl;		//マテリアルのハンドル
public:
	C3DUi();
	~C3DUi();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step(VECTOR _pos, float _rad,int _money);

};

