#pragma once
#include "sceneBase.h"
#include <DxLib.h>
#include"../ui/uiSelectManager.h"
#include"../map/mapManager.h"
#include"../sky/sky.h"
#include"../player/selectPlayer/selectPlayerManager.h"

//ゲーム本編を管理するクラス
class CSelectScene :public CSceneBase
{
private:
	CUiSelectManager		m_uiManager;			//UIマネージャ
	CMapManager				m_mapManager;			//マップマネージャ
	CSky					m_sky;					//天球
	CSelectPlayerManager	m_selectPlayerManager;	//セレクトのプレイヤーマネージャ

public:

	//コンストラクタ
	CSelectScene();
	//デストラクタ
	~CSelectScene();

	//描画処理
	void Draw();

private:

	//初期化
	void Init();

	//データ読み込み
	void Load();

	//メイン処理
	void Step();

	//終了前処理
	void Exit();

};

