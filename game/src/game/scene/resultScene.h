#pragma once
#include "sceneBase.h"
#include <DxLib.h>
#include "../sky/sky.h"
#include "../map/mapManager.h"
#include "../player/resultPlayer/resultPlayerManager.h"
#include "../ui/uiResultManager.h"

//ゲーム本編を管理するクラス
class CResultScene :public CSceneBase
{
public:
	enum tagState
	{
		RANKING,			//順位決め
		GRAPH,				//グラフ表示
		NEXT_SCENE,			//次のシーンに移行

		STATE_NUM,			//状態の数
	};
private:
	CSky					m_sky;					//天球
	CMapManager				m_mapManager;			//マップ
	CResultPlayerManager	m_resultPlayerManager;	//リザルトプレイヤー
	CUiResultManager		m_uiManager;			//UIマネージャ
public:

	//コンストラクタ
	CResultScene();
	//デストラクタ
	~CResultScene();

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

