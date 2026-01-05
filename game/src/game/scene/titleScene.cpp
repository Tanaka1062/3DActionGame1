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
	//UIの描写
	m_uiManager.Draw();

	DrawFormatString(32, 32, GetColor(255, 0, 0), "タイトル");
}

//---------------------------
//初期化
//---------------------------
void CTitleScene::Init()
{
	//UIの初期化
	m_uiManager.Init();

}

//---------------------------
//データ読み込み
//---------------------------
void CTitleScene::Load()
{
	//UIの画像ロード
	m_uiManager.Load();

	CSoundManager::Play(CSoundManager::BGM_TITLE, DX_PLAYTYPE_LOOP);
}

//---------------------------
//メイン処理
//---------------------------
void CTitleScene::Step()
{
	//UIの毎フレームする処理
	m_uiManager.Step();

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
	//UIの終了処理
	m_uiManager.Exit();

	CSoundManager::StopAll();
}
