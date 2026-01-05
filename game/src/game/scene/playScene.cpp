#include "playScene.h"
#include "../../lib/collision/collision.h"
#include "../system/soundManager.h"
#include "../../lib/input/keyInput.h"
#include"../collisionManager/collisionManager.h"
#include "../../lib/effekseer/effekseer.h"
#include "../camera/cameraManager.h"

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
	m_shot.Draw();
	m_attackManager.Draw();
	m_itemManager.Draw();
	m_weaponManager.Draw();
	m_uiManager.Draw();
	m_playerManager.Draw();

	CCameraManager::Draw();

}

//---------------------------
//		初期化
//---------------------------
void CPlayScene::Init()
{
	m_ground.Init();
	m_sky.Init();
	m_playerManager.Init();
	m_shot.Init();
	m_itemManager.Init(&m_playerManager);
	m_weaponManager.Init();
	m_uiManager.Init(&m_playerManager,&m_itemManager);
	CCameraManager::Init(ZERO);
	CCameraManager::ChangeCamera(CCameraManager::CAMERA_ID_MAP);
	m_gameTime = CGameTime::GetInstance();
	m_gameTime->Init();
	m_winner = CWinner::GetInstance();
	m_winner->Init();
}

//---------------------------
//		データ読み込み
//---------------------------
void CPlayScene::Load()
{
	m_ground.Load(MAP_ID_GRASSLAND);
	m_sky.Load();
	m_playerManager.Load();
	m_shot.Load();
	m_itemManager.Load();
	m_weaponManager.Load();
	m_uiManager.Load();
}

//---------------------------
//		メイン処理
//---------------------------
void CPlayScene::Step()
{
	//各種計算処理を実行
	m_sky.Step();

	m_playerManager.Step(&m_attackManager,&m_shot, CCameraManager::GetRot().y);

	m_shot.Step();

	m_itemManager.Step(&m_playerManager);

	m_weaponManager.Step(m_playerManager);

	m_uiManager.Step();

	CCameraManager::Step(ZERO,0.0f);

	m_gameTime->Step();

	m_winner->Step(&m_playerManager);

	//当たり判定----------------------------------
	//敵の視界範囲とプレイヤーの当たり判定
	CCollisionManager::CheckHitPlayerToPlayer(m_playerManager);
	CCollisionManager::CheckHitPlayerToMap(m_playerManager, m_ground);
	CCollisionManager::CheckHitItemToMap(m_itemManager, m_ground);
	CCollisionManager::CheckHitPlayerToItem(m_playerManager, m_itemManager);
	CCollisionManager::CheckHitPlayerToPlayerAttack(m_playerManager, m_attackManager);
	CCollisionManager::CheckHitItemToItem(m_itemManager);
	CCollisionManager::CheckHitPlayerToShot(m_playerManager, m_shot);
	CCollisionManager::CheckHitCpuPlayerFOVToPlayer(m_playerManager);
	CCollisionManager::CheckHitCpuPlayerFOVToItem(m_playerManager, m_itemManager);
	//--------------------------------------------

	//すべての結果を反映させる
	m_ground.Update();
	m_sky.Update();
	m_playerManager.Update();
	m_shot.Update();
	m_attackManager.Update();
	m_itemManager.Update();
	m_weaponManager.Update(m_playerManager);
	CCameraManager::Update(ZERO);

	if (CKeyInput::IsTrg(KEY_SELECT) == true ||
		m_gameTime->GetTimeEnd() == true)
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
	m_playerManager.Exit();
	m_attackManager.Exit();
	m_shot.Exit();
	m_itemManager.Exit();
	m_weaponManager.Exit();
	m_uiManager.Exit();

	//エフェクトを全て消す
	CEffekseerCtrl::StopAll();
	CSoundManager::StopAll();
}

