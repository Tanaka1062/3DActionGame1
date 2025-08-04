#pragma once
#include "sceneBase.h"
#include "../player/player.h"
#include "../camera/cameraManager.h"
#include "../ground/ground.h"
#include "../shot/shotManager.h"
#include "../enemy/enemyManager.h"
#include "../sky/sky.h"
#include "../ui/scoreText.h"
#include "../../lib/2DUi/2DUi.h"
#include"../data.h"

//ゲーム本編を管理するクラス
class CPlayScene :public CSceneBase
{
private:

	CGround m_ground;			//背景
	CSky m_sky;					//空
	CPlayer m_player;			//プレイヤー
	CEnemyManager m_enemy;		//エネミー
	CShotManager m_shot;		//弾全般
	CCameraManager m_camera;	//カメラ
	CScoreText m_score;			//スコアテキスト
	C2DUi m_loadBackGround;		//ロード画面の背景

public:

	//コンストラクタ
	CPlayScene();
	//デストラクタ
	~CPlayScene();

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

