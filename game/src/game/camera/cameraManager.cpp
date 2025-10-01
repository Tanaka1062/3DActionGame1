#include "cameraManager.h"
#include "../data.h"
#include "../../lib/effekseer/effekseer.h"

//定義関連====================================
static const float CAMERA_NEAR = 1.0f;						//ニアー
static const float CAMERA_FAR = 5000.0f;					//ファー
static const float CAMERA_PERS = 60.0f * DX_PI_F / 180.0f;	//パース
static const float ASPECT_RATIO =							//アスペクト比
static_cast<float>(WINDOW_SIZE_X / WINDOW_SIZE_Y);
//============================================

//---------------------------
//		コンストラクタ
//---------------------------
CCameraManager::CCameraManager() {
	//初期カメラはプレイカメラ
	m_id = CAMERA_ID_PLAY;
}


//---------------------------
//			初期化
//---------------------------
void CCameraManager::Init()
{
	//カメラを設定
	m_camera[CAMERA_ID_PLAY] = new CPlayCamera;
	m_camera[CAMERA_ID_DEBUG] = new CDbugCamera;

	//カメラの初期化
	for (int i = 0; i < CAMERA_ID_NUM; i++)
	{
		m_camera[i]->Init();
	}

	//プレイカメラの初期化
	m_play.Init();
	//デバックカメラ初期化
	m_debug.Init();

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
void CCameraManager::Step()
{
	//カメラの処理
	m_camera[m_id];

	switch (m_id)
	{
		//ゲーム中のメインカメラ
	case CAMERA_ID_PLAY:
		m_play.Step();
		break;
		//デバック用カメラ
	case CAMERA_ID_DEBUG:
		m_debug.Step();
		break;
	}

	//カメラのモード切替
	//デバックモードに変更
	if (CheckHitKey(KEY_INPUT_B) != 0)
	{
		m_debug.SetPos(m_play.GetPos(),m_play.GetRot());

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
	m_rot = m_camera[CAMERA_ID_PLAY]->GetRot();

}

//---------------------------
//			画像処理
//---------------------------
void CCameraManager::Draw()
{
	switch (m_id)
	{
		//ゲーム中のメインカメラ
	case CAMERA_ID_PLAY:
		break;
		//デバック用カメラ
	case CAMERA_ID_DEBUG:
		m_debug.Draw();
		break;
	}

}

//---------------------------
//		カメラの更新
//---------------------------
void CCameraManager::Update(VECTOR _tagetPos)
{
	//カメラの座標
	VECTOR pos = ZERO;
	//カメラの角度
	VECTOR rot = ZERO;
	//カメラの上方向
	VECTOR upVec = ZERO;

	switch (m_id)
	{
		//ゲーム中のメインカメラ
	case CAMERA_ID_PLAY:
		m_play.Update(_tagetPos);
		break;
		//デバック用カメラ
	case CAMERA_ID_DEBUG:
		m_debug.Update();
		break;
	}

}

