#pragma once
#include "sceneBase.h"
#include <DxLib.h>
#include "../ui/uiMapSelectManager.h"

//マップ選択画面を管理するクラス
class CMapSelectScene :public CSceneBase
{
private:
	CUiMapSelectManager m_uiManager;		
public:

	//コンストラクタ
	CMapSelectScene();
	//デストラクタ
	~CMapSelectScene();

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

