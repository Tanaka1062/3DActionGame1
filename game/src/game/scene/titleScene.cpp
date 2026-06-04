#include "titleScene.h"
#include "../data.h"
#include"../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/sound/soundManager.h"
#include "../camera/cameraManager.h"
#include "../../lib/system/fade.h"

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
	case MAIN_WAIT:
		m_LoadBG.Draw();
		break;
	default:
		m_mapManager.Draw();
		m_sky.Draw();
		m_titlePlayerManager.Draw();
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
	m_mapManager.Init(MAP_ID_TITLE);
	m_sky.Init();
	CCameraManager::Init(CCameraManager::CAMERA_ID_TITLE,m_mapManager.GetMap());
	m_titlePlayerManager.Init();

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
		m_mapManager.Load();
		m_sky.Load();
		m_titlePlayerManager.Load(m_mapManager.GetMap());

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
			CSoundManager::Play(CSoundManager::BGM_TITLE, DX_PLAYTYPE_LOOP);
			m_state = MAIN_WAIT;
		}
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
	m_mapManager.Step();
	m_sky.Step();
	CCameraManager::Step(&m_mapManager);
	m_titlePlayerManager.Step();

	CCameraManager::Update();
	m_sky.Update();
	m_titlePlayerManager.Update();

	if (CheckHitKey(KEY_INPUT_R) == 1)
	{
		CControllerManager::Init();
	}

	if (CKeyInput::IsTrg(KEY_SELECT) == true ||
		CControllerManager::SetId() == true ||
		CControllerManager::IsTrg(BUTTON_B) == true)
	{
		CSoundManager::Play(CSoundManager::SE_TITLE_START,DX_PLAYTYPE_BACK);

		m_state = END_WAIT;
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
	m_mapManager.Exit();
	m_sky.Exit();
	CCameraManager::Exit();
	m_titlePlayerManager.Exit();

	CSoundManager::StopAll();
}

