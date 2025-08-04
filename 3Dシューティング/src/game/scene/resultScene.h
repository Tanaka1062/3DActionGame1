#pragma once
#include "sceneBase.h"
#include <DxLib.h>
#include "../../lib/2DUi/2DUi.h"
#include "../ui/scoreText.h"

//ゲーム本編を管理するクラス
class CResultScene :public CSceneBase
{
private:
	C2DUi m_backGround;		//背景
	C2DUi m_text;			//文字
	CScoreText m_score;		//スコア

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

