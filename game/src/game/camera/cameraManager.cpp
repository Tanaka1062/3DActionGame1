#include "cameraManager.h"
#include "../data.h"
#include "../../lib/effekseer/effekseer.h"
#include "mapCamera/mapCamera.h"
#include "selectCamera/selectCamera.h"
#include "resultCamera/resultCamera.h"
#include "titleCamera/titleCamera.h"

//定義関連====================================
constexpr float CAMERA_NEAR = 1.0f;						//ニアー
constexpr float CAMERA_FAR = 5000.0f;					//ファー
constexpr float CAMERA_PERS = 60.0f * DX_PI_F / 180.0f;	//パース
constexpr float ASPECT_RATIO =							//アスペクト比
WINDOW_SIZE_X / WINDOW_SIZE_Y;
//============================================

CCameraBase* CCameraManager::m_camera[CAMERA_ID_NUM];
CCameraManager::tagCAMERA_ID CCameraManager::m_id;
VECTOR CCameraManager::m_rot;

//---------------------------
//		コンストラクタ
//---------------------------
CCameraManager::CCameraManager() {
	for (int camera_i = 0; camera_i < CAMERA_ID_NUM; camera_i++)
	{
		m_camera[camera_i] = nullptr;
	}
}

//---------------------------
//		 デストラクタ
//---------------------------
CCameraManager::~CCameraManager()
{

}

//---------------------------
//			初期化
//---------------------------
void CCameraManager::Init(tagCAMERA_ID _camera,CMapBase* _map)
{
	m_id = _camera;

	//カメラを設定
	m_camera[CAMERA_ID_MAP] = new CMapCamera;
	m_camera[CAMERA_ID_TITLE] = new CTitleCamera;
	m_camera[CAMERA_ID_SELECT] = new CSelectCamera;
	m_camera[CAMERA_ID_RESULT] = new CResultCamera;

	//カメラの初期化
	for (int camera_i = 0; camera_i < CAMERA_ID_NUM; camera_i++)
	{
		m_camera[camera_i]->Init(_map);
	}

	// カメラのニアーファー設定
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	//エフェクシアのカメラ設定
	CEffekseerCtrl::SetProjectionMtx(CAMERA_PERS, ASPECT_RATIO, CAMERA_NEAR, CAMERA_FAR);

	//カメラの回転値を取得
	m_rot = { 0.0f,0.0f,0.0f };

}

//---------------------------
//	毎フレームする処理
//---------------------------
void CCameraManager::Step(CMapManager* _mapManager, CPlayerManager* _playerManager)
{
	if (m_id == CAMERA_ID_NONE)return;

	VECTOR playerPos = ZERO;

	if (m_id == CAMERA_ID_MAP && _playerManager != nullptr)
	{
		CMapCamera* mapCamera = dynamic_cast<CMapCamera*>(m_camera[m_id]);

		mapCamera->Step(_mapManager->GetMap()->GetStageId(), _playerManager);
	}
	else if(_mapManager != nullptr)
	{
		int mapStageId = _mapManager->GetMap()->GetStageId();
		m_camera[m_id]->Step(_mapManager->GetMap()->GetHndl(mapStageId));
	}

	//カメラのモード切替

	//プレイカメラの回転値を設定
	m_rot = m_camera[m_id]->GetRot();

}

//---------------------------
//			画像処理
//---------------------------
void CCameraManager::Draw()
{
}

//---------------------------
//		カメラの更新
//---------------------------
void CCameraManager::Update()
{
	m_camera[m_id]->Update();

	//カメラの情報
	VECTOR pos = m_camera[m_id]->GetPos();
	VECTOR rot = m_camera[m_id]->GetRot();
	VECTOR up = m_camera[m_id]->GetUp();

	CEffekseerCtrl::SetCameraRotMtx(pos, rot, up);
	CEffekseerCtrl::UpdateAutoCamera();
}

//---------------------------
//			終了処理
//---------------------------
void CCameraManager::Exit()
{
	for (int camera_i = 0; camera_i < CAMERA_ID_NUM; camera_i++)
	{
		if (m_camera[camera_i] != nullptr) 
		{
			m_camera[camera_i]->Exit();

			delete m_camera[camera_i];

			m_camera[camera_i] = nullptr;
		}
	}
}

//---------------------------
//カメラが移動しているかを取得
//---------------------------
bool CCameraManager::GetIsMove()
{
	CMapCamera* mapCamera = dynamic_cast<CMapCamera*>(m_camera[CAMERA_ID_MAP]);
	return mapCamera->GetIsMove();
}

