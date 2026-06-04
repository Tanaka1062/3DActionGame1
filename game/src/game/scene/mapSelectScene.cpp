#include "mapSelectScene.h"
#include "../data.h"
#include"../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/sound/soundManager.h"
#include "../../lib/system/fade.h"

//定義関連====================================
//============================================

//---------------------------
//コンストラクタ
//---------------------------
CMapSelectScene::CMapSelectScene() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//デストラクタ
//---------------------------
CMapSelectScene::~CMapSelectScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}


//---------------------------
//描画処理
//---------------------------
void CMapSelectScene::Draw()
{
	switch (m_state)
	{
	case CSceneBase::LOAD:
	case MAIN_WAIT:
		m_LoadBG.Draw();
		break;
	default:
		m_bg.Draw();
		m_uiManager.Draw();
		break;
	}

}

//---------------------------
//初期化
//---------------------------
void CMapSelectScene::Init()
{
	CSceneBase::Init();
	m_bg.Init();
	m_uiManager.Init();
}

//---------------------------
//データ読み込み
//---------------------------
void CMapSelectScene::Load()
{
	CSceneBase::Load();
	switch (m_LoadState)
	{
	case 0:
		m_bg.Load();
		m_uiManager.Load();

		m_LoadState = 1;
		break;
	case 1:
		if (GetASyncLoadNum() == 0)
		{
			m_LoadState = 2;
			CFade::RequestFadeOut();
		}
		break;

	case 2:
		if (CFade::IsEndFadeOut() == true)
		{
			SetUseASyncLoadFlag(FALSE);
			CSoundManager::Play(CSoundManager::BGM_SELECT, DX_PLAYTYPE_LOOP);
			m_state = MAIN_WAIT;
		}
		break;
	}

}

//---------------------------
//メイン処理
//---------------------------
void CMapSelectScene::Step()
{
	m_bg.Step();
	m_uiManager.Step();

	if (CKeyInput::IsTrg(KEY_SELECT) == true ||
		m_uiManager.GetIsMapSelect())
	{
		m_state = END_WAIT;
	}

}

//---------------------------
//終了前処理
//---------------------------
void CMapSelectScene::Exit()
{
	m_bg.Exit();
	CSceneBase::Exit();
	m_uiManager.Exit();
	CSoundManager::StopAll();
}

