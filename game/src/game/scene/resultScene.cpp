#include "resultScene.h"
#include "../data.h"
#include "../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/soundManager.h"

//定義関連====================================
static const char BACKGROUND_HNDL_PATH[] = "data/graphic/result/backGround.png";		//背景の画像パス
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

	m_winner = CWinner::GetInstance();

	DrawFormatString(32, 32, GetColor(255, 0, 0), "リザルト");

	VECTOR pos;
	pos.x = static_cast<float>(WINDOW_SIZE_X / 2);
	pos.y = static_cast<float>(WINDOW_SIZE_Y / 2);

	switch (m_winner->GetWinnerPlayerName())
	{
	case PLAYER_1:
	DrawFormatString(pos.x, pos.y, GetColor(255, 0, 0), "プレイヤー１勝利");
		break;
	case PLAYER_2:
		DrawFormatString(pos.x, pos.y, GetColor(255, 0, 0), "プレイヤー2勝利");
		break;
	case PLAYER_3:
		DrawFormatString(pos.x, pos.y, GetColor(255, 0, 0), "プレイヤー3勝利");
		break;
	case PLAYER_4:
		DrawFormatString(pos.x, pos.y, GetColor(255, 0, 0), "プレイヤー4勝利");
		break;
	}

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

}

//---------------------------
//データ読み込み
//---------------------------
void CResultScene::Load()
{
	m_backGround.Load(BACKGROUND_HNDL_PATH);

}

//---------------------------
//メイン処理
//---------------------------
void CResultScene::Step()
{
	if (CKeyInput::IsTrg(KEY_SELECT) ||
		CControllerManager::IsTrg(BUTTON_A))
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

	CSoundManager::StopAll();
}
