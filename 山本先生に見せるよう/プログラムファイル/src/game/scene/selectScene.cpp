#include "selectScene.h"
#include "../data.h"
#include"../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/soundManager.h"
#include "../camera/cameraManager.h"

//定義関連====================================
//============================================

//---------------------------
//コンストラクタ
//---------------------------
CSelectScene::CSelectScene() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//デストラクタ
//---------------------------
CSelectScene::~CSelectScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}


//---------------------------
//描画処理
//---------------------------
void CSelectScene::Draw()
{
	switch (m_state)
	{
	case CSceneBase::LOAD:
		m_LoadBG.Draw();
		break;
	default:
		CCameraManager::Draw();
		m_map.Draw();
		m_sky.Draw();
		m_selectPlayerManager.Draw();
		//UIの画像表示
		m_uiManager.Draw();

		break;
	}

}

//---------------------------
//初期化
//---------------------------
void CSelectScene::Init()
{
	CSceneBase::Init();

	CCameraManager::Init(ZERO);
	CCameraManager::ChangeCamera(CCameraManager::CAMERA_ID_SELECT);
	m_map.Init();
	m_sky.Init();
	m_selectPlayerManager.Init();

	//UIの初期設定
	m_uiManager.Init();

}

//---------------------------
//データ読み込み
//---------------------------
void CSelectScene::Load()
{
	CSceneBase::Load();
	switch (m_LoadState)
	{
	case 0:
		m_map.Load(MAP_ID_SELECT);
		m_sky.Load();
		m_selectPlayerManager.Load();

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
		CSoundManager::Play(CSoundManager::BGM_SELECT, DX_PLAYTYPE_LOOP);
		m_state = MAIN;
		break;
	}

}

//---------------------------
//メイン処理
//---------------------------
void CSelectScene::Step()
{
	CCameraManager::Step(ZERO,0.0f);
	m_sky.Step();
	m_selectPlayerManager.Step();

	//UIの毎フレームする処理
	m_uiManager.Step(m_selectPlayerManager.GetIsAllReady());

	CCameraManager::Update(ZERO);
	m_sky.Update();
	m_selectPlayerManager.Update();

	//コントローラーをセット
	CControllerManager::SetId();

	//スペースで終わる
	if (CKeyInput::IsTrg(KEY_SELECT) ||
		m_uiManager.GetCountDownEnd() == true)
	{
		m_state = END;
	}

}

//---------------------------
//終了前処理
//---------------------------
void CSelectScene::Exit()
{
	CSceneBase::Exit();
	m_map.Exit();
	m_sky.Exit();
	m_selectPlayerManager.Exit();
	CCameraManager::Exit();

	//UIの終了処理
	m_uiManager.Exit();

	CSoundManager::StopAll();
}

