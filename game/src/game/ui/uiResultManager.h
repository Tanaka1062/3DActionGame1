#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <vector>
#include "../map/mapBase.h"
#include "resultLineGraph/resultLineGraph.h"

class CUiResultManager
{
private:
	std::vector<C2DObject*>	m_ui;		//UI
	CResultLineGraph		m_lineGraph;//折れ線グラフ
public:
	//コンストラクタ・デストラクタ
	CUiResultManager();
	~CUiResultManager();

	void Init();
	//ロード
	void Load();
	//毎フレームする処理
	void Step(CMapBase* _map);
	//描写
	void Draw();
	//破棄
	void Exit();

};

