#include "playScene.h"
#include "../../lib/collision/collision.h"
#include "../system/soundManager.h"
#include "../../lib/input/keyInput.h"
#include"../collisionManager/collisionManager.h"


//---------------------------
//		コンストラクタ
//---------------------------
CPlayScene::CPlayScene() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//		デストラクタ
//---------------------------
CPlayScene::~CPlayScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}


//---------------------------
//		描画処理
//---------------------------
void CPlayScene::Draw()
{
	m_ground.Draw();
	m_sky.Draw();
	m_goal.Draw();
	m_player.Draw();
	m_enemy.Draw();
	m_shot.Draw();

	m_camera.Draw();

}

//---------------------------
//		初期化
//---------------------------
void CPlayScene::Init()
{
	m_ground.Init();
	m_sky.Init();
	m_goal.Init();
	m_player.Init(&m_shot);
	m_enemy.Init();
	m_shot.Init();
	m_camera.Init();

}

//---------------------------
//		データ読み込み
//---------------------------
void CPlayScene::Load()
{
	m_ground.Load();
	m_sky.Load();
	m_goal.Load();
	m_player.Load();
	m_enemy.Load();
	m_shot.Load();

}

//---------------------------
//		メイン処理
//---------------------------
void CPlayScene::Step()
{
	//各種計算処理を実行
	m_sky.Step();

	m_player.Step(m_camera.GetRot().y);

	m_enemy.Step(m_player.GetCenter());

	m_shot.Step();

	m_camera.Step();


	//当たり判定----------------------------------
	//敵の視界範囲とプレイヤーの当たり判定
	CCollisionManager::CheckHitEnemyFOVToPlayer(m_enemy, m_player);
	CCollisionManager::CheckHitEnemyAttackToPlayer(m_enemy, m_player);
	CCollisionManager::CheckHitEnemyToPlayer(m_enemy, m_player);
	CCollisionManager::CheckHitEnemyToEnemy(m_enemy);
	CCollisionManager::CheckHitShotToEnemy(m_shot, m_enemy);
	//--------------------------------------------

	//すべての結果を反映させる
	m_ground.Update();
	m_sky.Update();
	m_goal.Update();
	m_player.Update();
	m_enemy.Update();
	m_shot.Update();
	m_camera.Update(m_player.GetCenter());

	if (CKeyInput::IsTrg(KEY_SELECT) == true ||
		m_player.GetActive() == false )
	{
		m_state = END;
	}

}

//---------------------------
//		終了前処理
//---------------------------
void CPlayScene::Exit()
{
	m_ground.Exit();
	m_sky.Exit();
	m_goal.Exit();
	m_player.Exit();
	m_enemy.Exit();

	CSoundManager::StopAll();
}
