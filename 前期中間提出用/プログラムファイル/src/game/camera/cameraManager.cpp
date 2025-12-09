#include "cameraManager.h"
#include "../data.h"

//定義関連====================================
static const float CAMERA_NEAR = 1.0f;				//ニアー
static const float CAMERA_FAR = 5000.0f;			//ファー
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
	//プレイカメラの初期化
	m_play.Init();
	//デバックカメラ初期化
	m_debug.Init();

	// カメラのニアーファー設定
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	//カメラの回転値を取得
	m_rot = { 0.0f,0.0f,0.0f };

}

//---------------------------
//	毎フレームする処理
//---------------------------
void CCameraManager::Step()
{
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

		m_id = CAMERA_ID_DEBUG;
	}
	//プレイモードに変更
	if (CheckHitKey(KEY_INPUT_C) != 0)
	{
		m_id = CAMERA_ID_PLAY;
	}

	//回転値を設定
	m_rot = m_play.GetRot();

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

