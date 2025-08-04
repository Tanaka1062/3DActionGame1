#include "resultScene.h"
#include "../data.h"
#include "../../lib/input.h"
#include "../score/scoreData.h"
#include "../system/soundManager.h"

//定義関連====================================
static const char BACKGROUND_HNDL_PATH[] = "data/graphic/result/resultBackGround.png";		//背景の画像パス
static const char TEXT_HNDL_PATH[] = "data/graphic/result/resultText.png";					//リザルトの文字の画像パス
//============================================

//---------------------------
//コンストラクタ
//---------------------------
CResultScene::CResultScene() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//デストラクタ
//---------------------------
CResultScene::~CResultScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}


//---------------------------
//描画処理
//---------------------------
void CResultScene::Draw()
{
	m_backGround.Draw();

	m_text.Draw();

	m_score.Draw();

	DrawFormatString(32, 32, GetColor(255, 0, 0), "リザルト");
}

//---------------------------
//初期化
//---------------------------
void CResultScene::Init()
{
	//背景の初期化
	VECTOR backGroundPos;
	backGroundPos.x = static_cast<float>(WINDOW_SIZE_X / 2);
	backGroundPos.y = static_cast<float>(WINDOW_SIZE_Y / 2);

	m_backGround.Init(backGroundPos);

	//テキストの初期化
	VECTOR textPos;
	textPos.x = static_cast<float>(WINDOW_SIZE_X / 2);
	textPos.y = static_cast<float>(WINDOW_SIZE_Y - 200);

	m_text.Init(textPos);

	m_score.Init();
	m_score.SetScore(CScoreData::GetScore());

	VECTOR scorePos;
	scorePos.x = static_cast<float>(WINDOW_SIZE_X / 2);
	scorePos.y = static_cast<float>(WINDOW_SIZE_Y / 2);

	m_score.SetPos(scorePos);
}

//---------------------------
//データ読み込み
//---------------------------
void CResultScene::Load()
{
	m_backGround.Load(BACKGROUND_HNDL_PATH);

	m_text.Load(TEXT_HNDL_PATH);

	m_score.Load();

	CSoundManager::Play(CSoundManager::BGM_RESULT, DX_PLAYTYPE_LOOP);

}

//---------------------------
//メイン処理
//---------------------------
void CResultScene::Step()
{
	//スペースで終わる
	if (CInput::IsInputTrg(KEY_SHOT))
	{
		m_state = END;
	}
}

//---------------------------
//終了前処理
//---------------------------
void CResultScene::Exit()
{
	m_backGround.Exit();

	m_text.Exit();

	m_score.Exit();

	CSoundManager::StopAll();
}
