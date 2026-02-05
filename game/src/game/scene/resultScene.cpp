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

	CWinner::DeleteInstance();
}


//---------------------------
//描画処理
//---------------------------
void CResultScene::Draw()
{
	switch (m_state)
	{
	case CSceneBase::LOAD:
		m_LoadBG.Draw();
		break;
	default:
		m_sky.Draw();
		m_map.Draw();
		m_resultPlayerManager.Draw();
		m_winPlayerText.Draw();
		m_resultText.Draw();

		break;
	}


}

//---------------------------
//初期化
//---------------------------
void CResultScene::Init()
{
	CSceneBase::Init();

	m_sky.Init();
	m_map.Init();
	m_resultPlayerManager.Init(m_winner->GetWinnerPlayerName());

	CCameraManager::Init(ZERO);
	CCameraManager::ChangeCamera(CCameraManager::CAMERA_ID_RESULT);

	VECTOR textPos = ZERO;
	textPos.x = WINDOW_SIZE_X * 0.5f;
	textPos.y = WINDOW_SIZE_Y * 0.5f;

	m_winPlayerText.Init(textPos);

	textPos.y += 200.0f;

	m_resultText.Init(textPos);
}

//---------------------------
//データ読み込み
//---------------------------
void CResultScene::Load()
{
	CSceneBase::Load();
	switch (m_LoadState)
	{
	case 0:
		m_sky.Load();
		m_map.Load(MAP_ID_RESULT);
		m_resultPlayerManager.Load();
		m_winPlayerText.Load(TEXT_GRAPHIC_PATH[m_winner->GetWinnerPlayerName()]);
		m_resultText.Load("data/graphic/result/resultText.png");
		CSoundManager::Play(CSoundManager::BGM_RESULT, DX_PLAYTYPE_LOOP);

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
		m_state = MAIN;
		break;
	}


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
	CSceneBase::Exit();
	m_sky.Exit();
	m_map.Exit();
	m_resultPlayerManager.Exit();
	m_winPlayerText.Exit();
	m_resultText.Exit();
	CCameraManager::Exit();

	CSoundManager::StopAll();
}

