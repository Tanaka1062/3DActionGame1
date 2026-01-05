#include "resultScene.h"
#include "../data.h"
#include "../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/soundManager.h"
#include "../camera/cameraManager.h"

//定義関連====================================
static const char* TEXT_GRAPHIC_PATH[PLAYER_NUM] =		//テキストのグラフィックパス
{
	"data/graphic/result/resultText1.png",
	"data/graphic/result/resultText2.png",
	"data/graphic/result/resultText3.png",
	"data/graphic/result/resultText4.png",

};
//============================================

//---------------------------
//コンストラクタ
//---------------------------
CResultScene::CResultScene() {
	//最初はデータ初期化
	m_state = INIT;

	m_winner = CWinner::GetInstance();
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
	m_sky.Draw();
	m_map.Draw();
	m_resultPlayerManager.Draw();

	DrawFormatString(32, 32, GetColor(255, 0, 0), "リザルト");

	m_winPlayerText.Draw();

	int posX = 0;
	int posY = 0;
	posX = WINDOW_SIZE_X / 2;
	posY = WINDOW_SIZE_Y / 2;

	switch (m_winner->GetWinnerPlayerName())
	{
	case PLAYER_1:
	DrawFormatString(posX, posY, GetColor(255, 0, 0), "プレイヤー１勝利");
		break;
	case PLAYER_2:
		DrawFormatString(posX, posY, GetColor(255, 0, 0), "プレイヤー2勝利");
		break;
	case PLAYER_3:
		DrawFormatString(posX, posY, GetColor(255, 0, 0), "プレイヤー3勝利");
		break;
	case PLAYER_4:
		DrawFormatString(posX, posY, GetColor(255, 0, 0), "プレイヤー4勝利");
		break;
	}

}

//---------------------------
//初期化
//---------------------------
void CResultScene::Init()
{
	m_sky.Init();
	m_map.Init();
	m_resultPlayerManager.Init(m_winner->GetWinnerPlayerName());

	CCameraManager::Init(ZERO);
	CCameraManager::ChangeCamera(CCameraManager::CAMERA_ID_RESULT);

	VECTOR textPos = ZERO;
	textPos.x = WINDOW_SIZE_X * 0.5f;
	textPos.y = WINDOW_SIZE_Y * 0.5f;

	m_winPlayerText.Init(textPos);
}

//---------------------------
//データ読み込み
//---------------------------
void CResultScene::Load()
{
	m_sky.Load();
	m_map.Load(MAP_ID_RESULT);
	m_resultPlayerManager.Load();
	m_winPlayerText.Load(TEXT_GRAPHIC_PATH[m_winner->GetWinnerPlayerName()]);
}

//---------------------------
//メイン処理
//---------------------------
void CResultScene::Step()
{
	m_sky.Step();
	m_map.Step();
	m_resultPlayerManager.Step();
	CCameraManager::Step(ZERO,0.0f);

	if (CKeyInput::IsTrg(KEY_SELECT) ||
		CControllerManager::IsTrg(BUTTON_B))
	{
		m_state = END;
	}

	m_sky.Update();
	m_map.Update();
	m_resultPlayerManager.Update();
	CCameraManager::Update(ZERO);
}

//---------------------------
//終了前処理
//---------------------------
void CResultScene::Exit()
{
	m_sky.Exit();
	m_map.Exit();
	m_resultPlayerManager.Exit();
	m_winPlayerText.Exit();

	CSoundManager::StopAll();
}
