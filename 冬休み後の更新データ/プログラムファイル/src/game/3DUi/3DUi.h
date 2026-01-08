#pragma once
#include "../../lib/model/3DObject.h"
#include <vector>
#include <iostream>

enum tag3DUiType
{
	UI_TYPE_NONE = -1,
	UI_TYPE_COIN,
	UI_TYPE_COIN_COST,

	UI_TYPE_NUM,
};

class C3DUi :public CObject
{
private:
	std::vector<int>m_materialHndl;		//マテリアルのハンドル
	tag3DUiType m_type;					//タイプ
public:
	C3DUi();
	~C3DUi();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step(VECTOR _pos, float _rad,int _money, tag3DUiType _type);

};

