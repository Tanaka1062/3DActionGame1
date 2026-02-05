#include "sceneManager.h"
#include "playScene.h"
#include "titleScene.h"
#include "resultScene.h"
#include "selectScene.h"
#include"../system/soundManager.h"
#include"../../lib/effekseer/effekseer.h"
#include "../gameTime/gameTime.h"

//定義関連====================================

//============================================

//---------------------------
//コンストラクタ
//---------------------------
CSceneManager::CSceneManager() {
	//最初はデータ初期化
	m_sceneID = TITLE;

	m_scene = new CTitleScene;

	CSoundManager::Init();
	CSoundManager::Load();
}

//---------------------------
//デストラクタ
//---------------------------
CSceneManager::~CSceneManager() {

	delete m_scene;

	CGameTime::DeleteInstance();
	CSoundManager::Exit();
}

//---------------------------
//実行処理
//---------------------------
int CSceneManager::Loop()
{
	//ゲームが終了したかを外部に伝えるため
	int result = -1;

	Factory();

	//本編が終了したかどうかを外部に伝える
	return result;
}

void CSceneManager::Factory()
{
	if (m_scene->Loop() != -1)
	{
		delete m_scene;
		switch (m_sceneID)
		{
		case TITLE:
			m_sceneID = SELECT;
			m_scene = new CSelectScene;
			break;
		case SELECT:
			m_sceneID = GAME;
			m_scene = new CPlayScene;
			break;
		case GAME:
			m_sceneID = RESULT;
			m_scene = new CResultScene;
			break;
		case RESULT:
			m_sceneID = TITLE;
			m_scene =  new CTitleScene;
			break;
		}
	}
}

	//---------------------------
	//描画処理
	//---------------------------
	void CSceneManager::Draw()
	{

		m_scene->Draw();

	}

