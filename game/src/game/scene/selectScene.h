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
	CUiSelectManager m_uiManager;
	CMapManager m_mapManager;
	CSky m_sky;
	CSelectPlayerManager m_selectPlayerManager;

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

