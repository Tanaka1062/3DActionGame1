#pragma once
#include "../../lib/model/3DObject.h"
#include <vector>
#include <iostream>

using namespace std;

class C3DUi :public CObject
{
private:
	vector<int>m_materialHndl;		//マテリアルのハンドル
public:
	C3DUi();
	~C3DUi();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step(VECTOR _pos, float _rad,float _cameraRotY,int _money);

};

