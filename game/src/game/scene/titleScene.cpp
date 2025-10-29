#include "titleScene.h"
#include "../data.h"
#include"../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/soundManager.h"

//定義関連====================================
static const char BACKGROUND_HNDL_PATH[] = "data/graphic/title/backGround.png";		//背景の画像パス
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
	//背景の画像描写
	m_backGround.Draw();

	DrawFormatString(32, 32, GetColor(255, 0, 0), "タイトル");
}

//---------------------------
//初期化
//---------------------------
void CTitleScene::Init()
{
	//背景の初期化
	VECTOR backGroundPos;
	backGroundPos.x = static_cast<float>(WINDOW_SIZE_X / 2);
	backGroundPos.y = static_cast<float>(WINDOW_SIZE_Y / 2);

	m_backGround.Init(backGroundPos);

}

//---------------------------
//データ読み込み
//---------------------------
void CTitleScene::Load()
{

	//背景の画像ロード
	m_backGround.Load(BACKGROUND_HNDL_PATH);

	CSoundManager::Play(CSoundManager::BGM_TITLE, DX_PLAYTYPE_LOOP);
}

//---------------------------
//メイン処理
//---------------------------
void CTitleScene::Step()
{
	//スペースで終わる
	if (CKeyInput::IsTrg(KEY_SELECT) ||
		CControllerManager::SetId(PAD_1) == true)
	{
		m_state = END;
	}

}

//---------------------------
//終了前処理
//---------------------------
void CTitleScene::Exit()
{
	//背景の画像破棄
	m_backGround.Exit();

	CSoundManager::StopAll();
}
