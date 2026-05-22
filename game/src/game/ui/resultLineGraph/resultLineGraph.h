#pragma once
#include "../../lib/2D/2DObject.h"
#include "resultPlayerPanel/resultPlayerPanel.h"
#include "../../scene/resultScene.h"

class CResultLineGraph
{
private:
	int					m_lineLen;					//線の長さ
	C2DObject			m_ui;						//ui	
	CResultPlayerPanel	m_playerPanel[PLAYER_NUM];	//プレイヤーパネル
public:
	//コンストラクタ・デストラクタ
	CResultLineGraph();
	~CResultLineGraph();

	//初期化
	void Init();

	//ロード
	void Load();

	//毎フレームする処理
	void Step(CResultScene::tagState _state);

	//描写処理
	void Draw();

	//終了処理
	void Exit();
};

