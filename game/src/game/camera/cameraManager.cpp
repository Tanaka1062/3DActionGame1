#include "cameraManager.h"
#include "../data.h"
#include "../../lib/effekseer/effekseer.h"
#include "playCamera/playCamera.h"
#include "debugCamera/debugCamera.h"
#include "mapCamera/mapCamera.h"
#include "selectCamera/selectCamera.h"
#include "resultCamera/resultCamera.h"

//定義関連====================================
constexpr float CAMERA_NEAR = 1.0f;						//ニアー
constexpr float CAMERA_FAR = 5000.0f;					//ファー
constexpr float CAMERA_PERS = 60.0f * DX_PI_F / 180.0f;	//パース
constexpr float ASPECT_RATIO =							//アスペクト比
static_cast<float>(WINDOW_SIZE_X / WINDOW_SIZE_Y);
//============================================

CCameraBase* CCameraManager::m_camera[CAMERA_ID_NUM];
CCameraManager::tagCAMERA_ID CCameraManager::m_id;
VECTOR CCameraManager::m_rot;

//---------------------------
//		コンストラクタ
//---------------------------
CCameraManager::CCameraManager() {
	//初期カメラはプレイカメラ
	m_id = CAMERA_ID_MAP;

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
void CCameraManager::Init(VECTOR _focus)
{
	//カメラを設定
	m_camera[CAMERA_ID_PLAY] = new CPlayCamera;
	m_camera[CAMERA_ID_MAP] = new CMapCamera;
	m_camera[CAMERA_ID_DEBUG] = new CDbugCamera;
	m_camera[CAMERA_ID_SELECT] = new CSelectCamera;
	m_camera[CAMERA_ID_RESULT] = new CResultCamera;

	//カメラの初期化
	for (int i = 0; i < CAMERA_ID_NUM; i++)
	{
		m_camera[i]->Init(_focus);
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
void CCameraManager::Step(VECTOR _focus, float _rot, tagMapCenterId _mapCenterId, CPlayerManager* _playerManager)
{
	VECTOR playerPos = ZERO;
	VECTOR focus = _focus;

	if (m_id == CAMERA_ID_MAP || _playerManager != nullptr)
	{
		CMapCamera* mapCamera = dynamic_cast<CMapCamera*>(m_camera[m_id]);

		mapCamera->Step(focus, _rot, _mapCenterId, _playerManager);
	}
	else
	{
		m_camera[m_id]->Step(_focus, _rot);
	}

	//カメラのモード切替
	//デバックモードに変更
	if (CheckHitKey(KEY_INPUT_B) != 0)
	{
		//変更前のカメラの座標
		VECTOR pos = m_camera[m_id]->GetPos();
		//変更前のカメラの角度
		VECTOR rot = m_camera[m_id]->GetRot();

		//デバックカメラに座標と角度を設定
		m_camera[CAMERA_ID_DEBUG]->SetPos(pos);
		m_camera[CAMERA_ID_DEBUG]->SetRot(rot);

		m_id = CAMERA_ID_DEBUG;
	}
	//プレイモードに変更
	if (CheckHitKey(KEY_INPUT_C) != 0)
	{
		m_id = CAMERA_ID_PLAY;
	}

	//プレイカメラの回転値を設定
	m_rot = m_camera[m_id]->GetRot();

}

//---------------------------
//			画像処理
//---------------------------
void CCameraManager::Draw()
{
	//デバックカメラの描写処理
	if (m_id == CAMERA_ID_DEBUG)
	{
		CDbugCamera* camera = dynamic_cast<CDbugCamera*>(m_camera[m_id]);
		camera->Draw();
	}
}

//---------------------------
//		カメラの更新
//---------------------------
void CCameraManager::Update(VECTOR _tagetPos)
{
	//カメラの更新
	//プレイカメラの場合はプレイヤーの座標を入れる
	if (m_id == CAMERA_ID_PLAY)
	{
		CPlayCamera* camera = dynamic_cast<CPlayCamera*>(m_camera[m_id]);
		camera->Update(_tagetPos);
	}
	else
	{
		m_camera[m_id]->Update();
	}

	//カメラの情報
	VECTOR pos = m_camera[m_id]->GetPos();
	VECTOR rot = m_camera[m_id]->GetRot();
	VECTOR up = m_camera[m_id]->GetUp();

	CEffekseerCtrl::SetCameraRotMtx(pos, rot, up);
	CEffekseerCtrl::UpdateAutoCamera();
}

//終了処理
void CCameraManager::Exit()
{
	for (int camera_i = 0; camera_i < CAMERA_ID_NUM; camera_i++)
	{
		if (m_camera[camera_i] != nullptr) 
		{
			delete m_camera[camera_i];

			m_camera[camera_i] = nullptr;
		}
	}
}

