#include "playScene.h"
#include "../collision/collision.hManager.h"
#include "../system/soundManager.h"
#include"../score/scoreData.h"

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

	m_player.Draw();
	m_shot.Draw();
	m_enemy.Draw();

	m_camera.Draw();

	m_score.Draw();

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
	m_player.Init();
	m_shot.Init();
	m_enemy.Init();
	m_camera.Init();
	m_score.Init();
	CScoreData::Init();

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
	m_player.LoadModel(PLAYER_MODEL_PATH);
	m_shot.Load();
	m_enemy.Load();
	m_score.Load();

	CSoundManager::Play(CSoundManager::BGM_GAME,DX_PLAYTYPE_LOOP);
}

//---------------------------
//メイン処理
//---------------------------
void CPlayScene::Step()
{
	//各種計算処理を実行
	m_sky.Step();
	m_player.Step(m_shot);
	m_shot.Step();
	m_enemy.Step();
	m_camera.Step(m_player.GetPos(), m_player.GetRot().y);
	m_score.Step(CScoreData::GetScore());

	//当たり判定
	CCollisionManger::CheckHitShotToEnemy(m_shot, m_enemy);
	CCollisionManger::CheckHitPlayerToEnemy(m_player, m_enemy);

	if (m_player.GetActive() == false)
	{
		m_state = END;
	}

	//すべての結果を反映させる
	m_ground.Update();
	m_sky.Update();
	m_player.Update();
	m_shot.Update();
	m_enemy.Update();
	m_camera.Update();
}

//---------------------------
//終了前処理
//---------------------------
void CPlayScene::Exit()
{
	m_ground.Exit();
	m_sky.Exit();
	m_player.Exit();
	m_shot.Exit();
	m_enemy.Exit();
	m_score.Exit();

	CSoundManager::StopAll();
}
