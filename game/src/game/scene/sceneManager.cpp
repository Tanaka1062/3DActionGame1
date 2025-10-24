#include "sceneManager.h"
#include "playScene.h"
#include "titleScene.h"
#include "resultScene.h"
#include "selectScene.h"
#include"../system/soundManager.h"
#include"../../lib/effekseer/effekseer.h"

//定義関連====================================

//============================================

//---------------------------
//コンストラクタ
//---------------------------
CSceneManager::CSceneManager() {
	//最初はデータ初期化
	m_sceneID = TITLE;

	m_scene[0] = new CTitleScene;
	m_scene[1] = new CSelectScene;
	m_scene[2] = new CPlayScene;
	m_scene[3] = new CResultScene;

	CSoundManager::Init();
	CSoundManager::Load();
}

//---------------------------
//デストラクタ
//---------------------------
CSceneManager::~CSceneManager() {

	for (int i = 0; i < SCENE_NUM; i++)
	{
		delete m_scene[i];
	}

	CSoundManager::Exit();
}

//---------------------------
//実行処理
//---------------------------
int CSceneManager::Loop()
{
	//ゲームが終了したかを外部に伝えるため
	int result = -1;

	switch (m_sceneID)
	{
	case TITLE:
		if (m_scene[TITLE]->Loop() != -1)
		{
			m_sceneID = SELECT;

		}
		break;
	case SELECT:
		if (m_scene[SELECT]->Loop() != -1)
		{
			m_sceneID = GAME;

		}

		break;
	case GAME:
		if (m_scene[GAME]->Loop() != -1)
		{
			m_sceneID = RESULT;

		}
		break;
	case RESULT:
		if (m_scene[RESULT]->Loop() != -1)
		{
			m_sceneID = TITLE;

		}
		break;
	}

	//本編が終了したかどうかを外部に伝える
	return result;
}

//---------------------------
//描画処理
//---------------------------
void CSceneManager::Draw()
{
	switch (m_sceneID)
	{
	case TITLE:
		m_scene[TITLE]->Draw();
		break;
	case SELECT:
		m_scene[SELECT]->Draw();
		break;
	case GAME:
		m_scene[GAME]->Draw();
		break;
	case RESULT:
		m_scene[RESULT]->Draw();
		break;
	}
}

