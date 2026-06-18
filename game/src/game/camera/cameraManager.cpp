#include "cameraManager.h"
#include "../data.h"
#include "../../lib/effekseer/effekseer.h"
#include "mapCamera/mapCamera.h"
#include "selectCamera/selectCamera.h"
#include "resultCamera/resultCamera.h"
#include "titleCamera/titleCamera.h"

using namespace std;

unique_ptr<CCameraBase> CCameraManager::m_camera;
CCameraManager::tagCAMERA_ID CCameraManager::m_id;

//定義関連====================================
constexpr float CAMERA_NEAR = 1.0f;						//ニアー
constexpr float CAMERA_FAR = 5000.0f;					//ファー
constexpr float CAMERA_PERS = 60.0f * DX_PI_F / 180.0f;	//パース
constexpr float ASPECT_RATIO =							//アスペクト比
WINDOW_SIZE_X / WINDOW_SIZE_Y;
//============================================


//---------------------------
//		 デストラクタ
//---------------------------
CCameraManager::~CCameraManager()
{
	Exit();
}

//---------------------------
//			初期化
//---------------------------
void CCameraManager::Init(tagCAMERA_ID _camera,CMapBase* _map)
{
	m_id = _camera;

	//カメラを設定
	switch (_camera)
	{
	case CCameraManager::CAMERA_ID_MAP:
		m_camera = make_unique<CMapCamera>();
		break;
	case CCameraManager::CAMERA_ID_TITLE:
		m_camera = make_unique<CTitleCamera>();
		break;
	case CCameraManager::CAMERA_ID_SELECT:
		m_camera = make_unique<CSelectCamera>();
		break;
	case CCameraManager::CAMERA_ID_RESULT:
		m_camera = make_unique<CResultCamera>();
		break;
	}

	//カメラの初期化
	m_camera->Init(_map);

	// カメラのニアーファー設定
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	//エフェクシアのカメラ設定
	CEffekseerCtrl::SetProjectionMtx(CAMERA_PERS, ASPECT_RATIO, CAMERA_NEAR, CAMERA_FAR);
}

//---------------------------
//	毎フレームする処理
//---------------------------
void CCameraManager::Step(CMapManager* _mapManager, CPlayerManager* _playerManager)
{
	if (m_id == CAMERA_ID_NONE)return;

	VECTOR playerPos = V_ZERO;

	if (m_id == CAMERA_ID_MAP && _playerManager != nullptr)
	{
		CMapCamera* mapCamera = dynamic_cast<CMapCamera*>(m_camera.get());

		mapCamera->Step(_mapManager->GetMap()->GetStageId(), _playerManager);
	}
	else if(_mapManager != nullptr)
	{
		int mapStageId = _mapManager->GetMap()->GetStageId();
		m_camera->Step(_mapManager->GetMap()->GetHndl(mapStageId));
	}
}

//---------------------------
//		カメラの更新
//---------------------------
void CCameraManager::Update()
{
	m_camera->Update();

	//カメラの情報
	VECTOR pos = m_camera->GetPos();
	VECTOR rot = m_camera->GetRot();
	VECTOR up = m_camera->GetUp();

	CEffekseerCtrl::SetCameraRotMtx(pos, rot, up);
	CEffekseerCtrl::UpdateAutoCamera();
}

//---------------------------
//			終了処理
//---------------------------
void CCameraManager::Exit()
{
	if (m_camera != nullptr)
	{
		m_camera->Exit();
		m_camera.reset();
	}
}

//---------------------------
//カメラが移動しているかを取得
//---------------------------
bool CCameraManager::GetIsMove()
{
	if (m_id == CAMERA_ID_MAP)
	{
		CMapCamera* mapCamera = dynamic_cast<CMapCamera*>(m_camera.get());
		return mapCamera->GetIsMove();
	}
	return false;
}

