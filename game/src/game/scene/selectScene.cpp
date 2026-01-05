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
	Init();
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
	CCameraManager::Draw();
	m_map.Draw();
	m_sky.Draw();
	m_selectPlayerManager.Draw();

	//UIの画像表示
	//m_uiManager.Draw();

	DrawFormatString(32, 32, GetColor(255, 0, 0), "セレクト");

	DrawFormatString(32, 64, GetColor(255, 0, 0), "コントローラー");

}

//---------------------------
//初期化
//---------------------------
void CSelectScene::Init()
{
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
	m_map.Load(MAP_ID_SELECT);
	m_sky.Load();
	m_selectPlayerManager.Load();

	//UIの画像ロード
	m_uiManager.Load();

	CSoundManager::Play(CSoundManager::BGM_TITLE, DX_PLAYTYPE_LOOP);
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
	m_uiManager.Step();

	CCameraManager::Update(ZERO);
	m_sky.Update();
	m_selectPlayerManager.Update();

	//コントローラーをセット
	CControllerManager::SetId();

	//スペースで終わる
	if (CKeyInput::IsTrg(KEY_SELECT) ||
		m_selectPlayerManager.GetIsAllReady() == true)
	{
		m_state = END;
	}

}

//---------------------------
//終了前処理
//---------------------------
void CSelectScene::Exit()
{
	m_map.Exit();
	m_sky.Exit();
	m_selectPlayerManager.Exit();

	//UIの終了処理
	m_uiManager.Exit();

	CSoundManager::StopAll();
}

