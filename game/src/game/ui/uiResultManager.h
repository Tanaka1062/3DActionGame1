#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <vector>
#include "resultLineGraph/resultLineGraph.h"

class CUiResultManager
{
private:
	enum tagState
	{
		RANKING,				//順位決め
		GRAPH,					//グラフ表示
	};

	std::vector<C2DObject*>	m_ui;			//UI
	CResultLineGraph		m_lineGraph;	//折れ線グラフ
	tagState				m_state;		//状態
	bool					m_isGraphEnd;	//グラフ終了フラグ
public:
	//コンストラクタ・デストラクタ
	CUiResultManager();
	~CUiResultManager();

	void Init();
	//ロード
	void Load();
	//毎フレームする処理
	void Step(bool _isPodiumMoveEnd);
	//描写
	void Draw();
	//破棄
	void Exit();

	//グラフ終了フラグを取得
	bool GetIsGraphEnd() { return m_isGraphEnd; }
};

