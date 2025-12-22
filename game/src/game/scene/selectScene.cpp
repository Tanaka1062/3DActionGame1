#include "selectScene.h"
#include "../data.h"
#include"../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/soundManager.h"

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
	//UIの画像表示
	m_uiManager.Draw();

	DrawFormatString(32, 32, GetColor(255, 0, 0), "セレクト");

	DrawFormatString(32, 64, GetColor(255, 0, 0), "コントローラー");

}

//---------------------------
//初期化
//---------------------------
void CSelectScene::Init()
{
	//UIの初期設定
	m_uiManager.Init();

}

//---------------------------
//データ読み込み
//---------------------------
void CSelectScene::Load()
{
	//UIの画像ロード
	m_uiManager.Load();

	CSoundManager::Play(CSoundManager::BGM_TITLE, DX_PLAYTYPE_LOOP);
}

//---------------------------
//メイン処理
//---------------------------
void CSelectScene::Step()
{
	//UIの毎フレームする処理
	m_uiManager.Step();

	//コントローラーをセット
	CControllerManager::SetId();

	//スペースで終わる
	if (CKeyInput::IsTrg(KEY_SELECT) ||
		CControllerManager::IsAllConnection() == true)
	{
		m_state = END;
	}

}

//---------------------------
//終了前処理
//---------------------------
void CSelectScene::Exit()
{
	//UIの終了処理
	m_uiManager.Exit();

	CSoundManager::StopAll();
}

