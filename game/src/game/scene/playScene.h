#pragma once
#include "sceneBase.h"
#include "../camera/cameraManager.h"
#include "../map/map.h"
#include "../sky/sky.h"
#include"../data.h"
#include"../character/characterBase.h"
#include<iostream>
#include<vector>

using namespace std;

//ゲーム本編を管理するクラス
class CPlayScene :public CSceneBase
{
private:

	CGround m_ground;					//背景
	CSky m_sky;							//空
	CCameraManager m_camera;			//カメラ
	vector<CCharacterBase*> m_chara;	//キャラクター

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

