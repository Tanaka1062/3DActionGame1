#include "titleScene.h"
#include "../data.h"
#include"../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/soundManager.h"

//定義関連====================================
//============================================

//---------------------------
//コンストラクタ
//---------------------------
CTitleScene::CTitleScene() {
	//最初はデータ初期化
	m_state = INIT;
	Init();
}

//---------------------------
//デストラクタ
//---------------------------
CTitleScene::~CTitleScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}


//---------------------------
//描画処理
//---------------------------
void CTitleScene::Draw()
{
	switch (m_state)
	{
	case CSceneBase::LOAD:
		m_LoadBG.Draw();
		break;
	default:
		//UIの描写
		m_uiManager.Draw();

		break;
	}

}

//---------------------------
//初期化
//---------------------------
void CTitleScene::Init()
{
	CSceneBase::Init();

	//UIの初期化
	m_uiManager.Init();
}

//---------------------------
//データ読み込み
//---------------------------
void CTitleScene::Load()
{
	CSceneBase::Load();
	switch (m_LoadState)
	{
	case 0:
		//UIの画像ロード
		m_uiManager.Load();

		m_LoadState = 1;
		break;
	case 1:
		if (GetASyncLoadNum() == 0)
		{
			m_LoadState = 2;
		}
		break;

	case 2:
		SetUseASyncLoadFlag(FALSE);
		CSoundManager::Play(CSoundManager::BGM_TITLE, DX_PLAYTYPE_LOOP);
		m_state = MAIN;
		break;
	}
}

//---------------------------
//メイン処理
//---------------------------
void CTitleScene::Step()
{
	//UIの毎フレームする処理
	m_uiManager.Step();

	if (CheckHitKey(KEY_INPUT_R) == 1)
	{
		CControllerManager::Init();
	}

	//スペースで終わる
	if (CKeyInput::IsTrg(KEY_SELECT) ||
		CControllerManager::SetId() == true ||
		CControllerManager::IsTrg(BUTTON_B) == true)
	{
		m_state = END;
	}

}

//---------------------------
//終了前処理
//---------------------------
void CTitleScene::Exit()
{
	CSceneBase::Exit();
	//UIの終了処理
	m_uiManager.Exit();

	CSoundManager::StopAll();
}

