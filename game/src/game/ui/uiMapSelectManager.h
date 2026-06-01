#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <vector>
#include "mapSelect/mapSelect.h"

class CUiMapSelectManager
{
private:
	CMapSelect m_mapSelect;		//マップセレクト
public:
	//コンストラクタ・デストラクタ
	CUiMapSelectManager();
	~CUiMapSelectManager();

	void Init();
	//ロード
	void Load();
	//毎フレームする処理
	void Step();
	//描写
	void Draw();
	//破棄
	void Exit();

};

