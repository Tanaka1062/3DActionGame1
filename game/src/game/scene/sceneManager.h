#pragma once
#include "sceneBase.h"

//ゲーム本編を管理するクラス
class CSceneManager
{
private:

	//ゲーム中に使用するシーン
	enum tagScene
	{
		TITLE,		//タイトル画面
		SELECT,		//セレクト画面
		GAME,		//ゲーム本編
		RESULT,		//リザルト画面

		SCENE_NUM,	//シーンの数
	};

	//各種シーン変数
	tagScene m_sceneID;	//今のシーン

	CSceneBase* m_scene;

	void Factory();

public:

	//コンストラクタ
	CSceneManager();
	//デストラクタ
	~CSceneManager();

	//実行処理
	int Loop();
	//描画処理
	void Draw();


};

