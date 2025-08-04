#include "titleScene.h"
#include "../data.h"
#include"../../lib/input/keyInput.h"
#include "../system/soundManager.h"

//定義関連====================================
static const char BACKGROUND_HNDL_PATH[] = "data/graphic/title/backGround.png";		//背景の画像パス
static const char START_TEXT_HNDL_PATH[] = "data/graphic/title/startText.png";		//スタートテキストの画像パス
static const char TITLE_HNDL_PATH[] = "data/graphic/title/titleText.png";			//タイトルテキストの画像パス
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
	//スタートテキストの画像描写
	m_startText.Draw(3.0f);

	//タイトルテキストの画像描写
	m_title.Draw(3.0f);

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

	//スタートテキストの初期化
	VECTOR startTextPos;
	startTextPos.x = static_cast<float>(WINDOW_SIZE_X / 2);
	startTextPos.y = static_cast<float>(WINDOW_SIZE_Y - 200);

	m_startText.Init(startTextPos);

	//タイトルの初期化
	VECTOR titlePos;
	titlePos.x = static_cast<float>(WINDOW_SIZE_X / 2);
	titlePos.y = 100.0f;

	m_title.Init(titlePos);
}

//---------------------------
//データ読み込み
//---------------------------
void CTitleScene::Load()
{

	//背景の画像ロード
	m_backGround.Load(BACKGROUND_HNDL_PATH);
	//スタートテキストの画像ロード
	m_startText.Load(START_TEXT_HNDL_PATH);
	//タイトルの画像ロード
	m_title.Load(TITLE_HNDL_PATH);

	CSoundManager::Play(CSoundManager::BGM_TITLE, DX_PLAYTYPE_LOOP);
}

//---------------------------
//メイン処理
//---------------------------
void CTitleScene::Step()
{
	//スペースで終わる
	if (CKeyInput::IsTrg(KEY_SELECT))
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
	//スタートテキストの画像破棄
	m_startText.Exit();
	//タイトルの画像破棄
	m_title.Exit();

	CSoundManager::StopAll();
}
