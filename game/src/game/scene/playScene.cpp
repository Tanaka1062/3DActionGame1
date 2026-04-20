#include "playScene.h"
#include "../../lib/collision/collision.h"
#include "../system/soundManager.h"
#include "../../lib/input/keyInput.h"
#include"../collisionManager/collisionManager.h"
#include "../../lib/effekseer/effekseer.h"
#include "../camera/cameraManager.h"
#include "../../lib/system/fade.h"

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
	
	switch (m_state)
	{
	case CSceneBase::LOAD:
	case MAINWAIT:
		m_LoadBG.Draw();
		break;
	default:
		m_mapManager.Draw();
		m_sky.Draw();
		m_shot.Draw();
		m_attackManager.Draw();
		m_itemManager.Draw();
		m_weaponManager.Draw();
		m_playerManager.Draw();
		m_3DUiManager->Draw();
		m_uiManager.Draw();

		//エフェクシアの描画処理
		CEffekseerCtrl::Draw();

		CCameraManager::Draw();
		break;
	}
	
}

//---------------------------
//		初期化
//---------------------------
void CPlayScene::Init()
{
	CSceneBase::Init();
	m_mapManager.Init(MAP_ID_GRASSLAND);
	m_sky.Init();
	m_playerManager.Init();
	m_shot.Init();
	m_itemManager.Init(&m_playerManager);
	m_weaponManager.Init();
	m_uiManager.Init(&m_playerManager,&m_itemManager);
	CCameraManager::Init(CCameraManager::CAMERA_ID_MAP,m_mapManager.GetMap());
	CCameraManager::ChangeCamera(CCameraManager::CAMERA_ID_MAP);
	m_gameTime = CGameTime::GetInstance();
	m_gameTime->Init();
	m_winner = CWinner::GetInstance();
	m_winner->Init();
	m_eventManager.Init();
	m_3DUiManager = C3DUiManager::GetInstance();
	m_3DUiManager->Init();
}

//---------------------------
//		データ読み込み
//---------------------------
void CPlayScene::Load()
{
	CSceneBase::Load();
	switch (m_LoadState)
	{
	case 0:
		m_mapManager.Load();
		m_sky.Load();
		m_playerManager.Load(m_mapManager.GetMap(),m_3DUiManager);
		m_shot.Load();
		m_itemManager.Load(m_mapManager.GetMap());
		m_weaponManager.Load();
		m_uiManager.Load();
		CSoundManager::Play(CSoundManager::BGM_GAME, DX_PLAYTYPE_LOOP);

		m_LoadState = 1;
		break;
	case 1:

		if (GetASyncLoadNum() == 0)
		{
			m_LoadState = 2;
			CFade::RequestFadeOut();
		}
		break;

	case 2:
		if (CFade::IsEndFadeOut() == true)
		{
			SetUseASyncLoadFlag(FALSE);
			m_state = MAINWAIT;
		}
		break;
	}

}

//---------------------------
//		メイン処理
//---------------------------
void CPlayScene::Step()
{
	//各種計算処理を実行
	m_mapManager.Step();
	m_sky.Step(CCameraManager::GetFocusPos());
	m_playerManager.Step(&m_attackManager,&m_shot,m_3DUiManager, CCameraManager::GetRot().y,m_mapManager.GetMap()->GetStageId());
	m_shot.Step();
	m_itemManager.Step(&m_playerManager,m_mapManager.GetMap()->GetStageId());
	m_weaponManager.Step(m_playerManager);
	m_uiManager.Step(m_eventManager.GetNowEventName(),m_playerManager);
	CCameraManager::Step(&m_mapManager, &m_playerManager);
	m_gameTime->Step();
	m_winner->Step(&m_playerManager);
	m_eventManager.Step(CCameraManager::GetFocusPos(),m_itemManager);

	//当たり判定----------------------------------
	//敵の視界範囲とプレイヤーの当たり判定
	CCollisionManager::CheckHitPlayerToPlayer(m_playerManager);
	CCollisionManager::CheckHitPlayerToMap(m_playerManager, m_mapManager.GetMap());
	CCollisionManager::CheckHitItemToMap(m_itemManager, m_mapManager.GetMap());
	CCollisionManager::CheckHitPlayerToItem(m_playerManager, m_itemManager);
	CCollisionManager::CheckHitPlayerToPlayerAttack(m_playerManager, m_attackManager);
	CCollisionManager::CheckHitItemToItem(m_itemManager);
	CCollisionManager::CheckHitPlayerToShot(m_playerManager, m_shot);
	CCollisionManager::CheckHitCpuPlayerFOVToPlayer(m_playerManager);
	CCollisionManager::CheckHitCpuPlayerFOVToItem(m_playerManager, m_itemManager);
	//--------------------------------------------

	//すべての結果を反映させる
	m_mapManager.Update();
	m_sky.Update();
	m_playerManager.Update();
	m_shot.Update();
	m_attackManager.Update();
	m_itemManager.Update();
	m_weaponManager.Update(m_playerManager);
	CCameraManager::Update();

	if (CKeyInput::IsTrg(KEY_SELECT) == true ||
		m_gameTime->GetTimeEnd() == true)
	{
		m_state = ENDWAIT;
	}


}

//---------------------------
//		終了前処理
//---------------------------
void CPlayScene::Exit()
{
	CSceneBase::Exit();
	m_mapManager.Exit();
	m_sky.Exit();
	m_playerManager.Exit();
	m_attackManager.Exit();
	m_shot.Exit();
	m_itemManager.Exit();
	m_weaponManager.Exit();
	m_uiManager.Exit();
	m_eventManager.Exit();
	m_3DUiManager->Exit();
	C3DUiManager::DeleteInstance();
	CCameraManager::Exit();

	//エフェクトを全て消す
	CEffekseerCtrl::StopAll();
	CSoundManager::StopAll();
}

