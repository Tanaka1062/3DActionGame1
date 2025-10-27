#include "playScene.h"
#include "../../lib/collision/collision.h"
#include "../system/soundManager.h"
#include "../../lib/input/keyInput.h"
#include"../collisionManager/collisionManager.h"
#include "../../lib/effekseer/effekseer.h"


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
	m_playerManager.Draw();
	m_enemy.Draw();
	m_shot.Draw();
	m_attackManager.Draw();
	m_item.Draw();
	m_itemInventory.Draw();
	m_weapon.Draw();
	m_box.Draw();

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
	m_playerManager.Init(&m_attackManager);
	m_enemy.Init();
	m_shot.Init();
	m_item.Init(&m_player,&m_shot);
	m_itemInventory.Init(&m_player);
	m_weapon.Init();
	m_box.Init();
	m_camera.Init(m_player.GetCenter());

}

//---------------------------
//		データ読み込み
//---------------------------
void CPlayScene::Load()
{
	m_ground.Load();
	m_sky.Load();
	m_goal.Load();
	m_playerManager.Load();
	m_enemy.Load();
	m_shot.Load();
	m_item.Load();
	m_weapon.Load();
	m_box.Load();
}

//---------------------------
//		メイン処理
//---------------------------
void CPlayScene::Step()
{
	//各種計算処理を実行
	m_sky.Step();

	m_playerManager.Step(m_camera.GetRot().y);

	m_enemy.Step(m_player.GetCenter());

	m_shot.Step();

	m_item.Step();

	m_itemInventory.Step(&m_shot);

	m_box.Step(&m_item);

	m_camera.Step(m_player.GetCenter(),m_player.GetRad());


	//当たり判定----------------------------------
	//敵の視界範囲とプレイヤーの当たり判定
	CCollisionManager::CheckHitEnemyFOVToPlayer(m_enemy, m_player);
	CCollisionManager::CheckHitEnemyAttackToPlayer(m_enemy, m_player);
	CCollisionManager::CheckHitPlayerAttackToEnemy(m_attackManager, m_enemy);
	CCollisionManager::CheckHitEnemyToPlayer(m_enemy, m_player);
	CCollisionManager::CheckHitEnemyToEnemy(m_enemy);
	CCollisionManager::CheckHitShotToEnemy(m_shot, m_enemy);
	CCollisionManager::CheckHitPlayerToGoal(m_player, m_goal, m_enemy.GetIsAllDie());
	CCollisionManager::CheckHitPlayerToMap(m_player, m_ground);
	CCollisionManager::CheckHitEnemyToMap(m_enemy, m_ground);
	CCollisionManager::CheckHitItemToPlayer(m_item,m_itemInventory, m_player);
	CCollisionManager::CheckHitAttackToBox(m_attackManager, m_box);
	CCollisionManager::CheckHitPlayerToBox(m_player, m_box);
	CCollisionManager::CheckHitBoxToMap(m_box, m_ground);
	//--------------------------------------------

	//すべての結果を反映させる
	m_ground.Update();
	m_sky.Update();
	m_goal.Update();
	m_playerManager.Update();
	m_enemy.Update();
	m_shot.Update();
	m_attackManager.Update();
	m_item.Update();
	m_itemInventory.Update();
	m_weapon.Update(m_player.GetHndl());
	m_box.Update();
	m_camera.Update(m_player.GetCenter());

	if (CKeyInput::IsTrg(KEY_SELECT) == true ||
		m_player.GetActive() == false )
	{
		m_state = END;
	}

	if (m_goal.GetIsGoal() == true)
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
	m_playerManager.Exit();
	m_enemy.Exit();
	m_attackManager.Exit();
	m_shot.Exit();
	m_item.Exit();
	m_weapon.Exit();
	m_box.Exit();

	//エフェクトを全て消す
	CEffekseerCtrl::StopAll();
	CSoundManager::StopAll();
}

