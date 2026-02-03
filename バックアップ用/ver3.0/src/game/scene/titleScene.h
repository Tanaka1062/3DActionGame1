#pragma once
#include "sceneBase.h"
#include <DxLib.h>
#include "../ui/uiTitleManager.h"

//ゲーム本編を管理するクラス
class CTitleScene :public CSceneBase
{
private:
	CUiTitleManager m_uiManager;

public:

	//コンストラクタ
	CTitleScene();
	//デストラクタ
	~CTitleScene();

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

