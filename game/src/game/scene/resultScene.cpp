#include "resultScene.h"
#include "../data.h"
#include "../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"
#include "../system/sound/soundManager.h"
#include "../camera/cameraManager.h"
#include "../../lib/system/fade.h"
#include "../ranking/ranking.h"
#include "../map/resultMap/resultMap.h"

//---------------------------
//		コンストラクタ
//---------------------------
CResultScene::CResultScene() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//		デストラクタ
//---------------------------
CResultScene::~CResultScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();

	CRanking::DeleteInstance();
}


//---------------------------
//			描画処理
//---------------------------
void CResultScene::Draw()
{
	switch (m_state)
	{
	case CSceneBase::LOAD:
	case MAINWAIT:
		m_LoadBG.Draw();

		break;
	default:
		m_sky.Draw();
		m_mapManager.Draw();
		m_resultPlayerManager.Draw();
		m_uiManager.Draw();
		break;
	}


}

//---------------------------
//			初期化
//---------------------------
void CResultScene::Init()
{
	CSceneBase::Init();

	m_sky.Init();
	m_mapManager.Init(MAP_ID_RESULT);
	m_resultPlayerManager.Init();
	m_uiManager.Init();
	CCameraManager::Init(CCameraManager::CAMERA_ID_RESULT,m_mapManager.GetMap());
	CCameraManager::ChangeCamera(CCameraManager::CAMERA_ID_RESULT);
}

//---------------------------
//		データ読み込み
//---------------------------
void CResultScene::Load()
{
	CRanking* ranking = CRanking::GetInstance();
	CSceneBase::Load();
	switch (m_LoadState)
	{
	case 0:
		m_sky.Load();
		m_mapManager.Load();
		m_resultPlayerManager.Load(m_mapManager.GetMap());
		m_uiManager.Load();
		CSoundManager::Play(CSoundManager::BGM_DRUMROLL, DX_PLAYTYPE_LOOP);

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
//		  メイン処理
//---------------------------
void CResultScene::Step()
{
	bool isPodiumMoveEnd = false;

	if (m_mapManager.GetMap()->GetMapId() == MAP_ID_RESULT)
	{
		CResultMap* resultMap = dynamic_cast<CResultMap*>(m_mapManager.GetMap());
		isPodiumMoveEnd = resultMap->GetIsPodiumAllMoveEnd();
	}

	m_sky.Step();
	m_mapManager.Step();
	m_resultPlayerManager.Step(m_mapManager.GetMap());
	m_uiManager.Step(isPodiumMoveEnd);
	CCameraManager::Step(&m_mapManager);

	if (m_uiManager.GetIsGraphEnd() == true)
	{
		m_state = ENDWAIT;
	}

	m_sky.Update();
	m_mapManager.Update();
	m_resultPlayerManager.Update();
	CCameraManager::Update();
}

//---------------------------
//		  終了前処理
//---------------------------
void CResultScene::Exit()
{
	CSceneBase::Exit();
	m_sky.Exit();
	m_mapManager.Exit();
	m_resultPlayerManager.Exit();
	m_uiManager.Exit();
	CCameraManager::Exit();

	CSoundManager::StopAll();
}

