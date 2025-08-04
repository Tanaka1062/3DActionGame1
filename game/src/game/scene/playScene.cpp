#include "playScene.h"
#include "../../lib/collision/collision.h"
#include "../system/soundManager.h"

//定義関連====================================
static const char LOAD_BACKGROUND_GRAPHIC_PATH[] = "data/graphic/game/LoadBackGround.png";
//============================================

//---------------------------
//コンストラクタ
//---------------------------
CPlayScene::CPlayScene() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//デストラクタ
//---------------------------
CPlayScene::~CPlayScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}


//---------------------------
//描画処理
//---------------------------
void CPlayScene::Draw()
{
	m_ground.Draw();
	m_sky.Draw();

	m_camera.Draw();


	if (m_state == LOAD)
	{
		m_loadBackGround.Draw();
	}
}

//---------------------------
//初期化
//---------------------------
void CPlayScene::Init()
{
	m_ground.Init();
	m_sky.Init();
	m_camera.Init();

	VECTOR loadBGPos;
	loadBGPos.x = static_cast<float>(WINDOW_SIZE_X / 2);
	loadBGPos.y = static_cast<float>(WINDOW_SIZE_Y / 2);
	m_loadBackGround.Init(loadBGPos);
}

//---------------------------
//データ読み込み
//---------------------------
void CPlayScene::Load()
{
	m_loadBackGround.Load(LOAD_BACKGROUND_GRAPHIC_PATH);
	m_ground.LoadModel(GROUND_MODEL_PATH);
	m_sky.LoadModel(SKY_MODEL_PATH);

}

//---------------------------
//メイン処理
//---------------------------
void CPlayScene::Step()
{
	//各種計算処理を実行
	m_sky.Step();

	//当たり判定


	//すべての結果を反映させる
	m_ground.Update();
	m_sky.Update();
	m_camera.Update();
}

//---------------------------
//終了前処理
//---------------------------
void CPlayScene::Exit()
{
	m_ground.Exit();
	m_sky.Exit();

	CSoundManager::StopAll();
}
