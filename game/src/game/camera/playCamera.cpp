#include "PlayCamera.h"
#include <math.h>
#include"../../lib/input/keyInput.h"

//定義関連====================================
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const float CAMERA_BACK = 30.0f;				//カメラとプレイヤーの距離
static const float CAMERA_OFFSET_Y = 10.0f;			//カメラの修正Y
static const float TARGET_OFFSET_Y = 5.0f;			//ターゲットの修正Y
static const float ROT_Y_SPEED = 0.1f;				//カメラのY軸回転スピード
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CPlayCamera::CPlayCamera() {
	m_cameraPos = ZERO;
	m_tagetPos = ZERO;
	m_upVec = ZERO;
	m_rot = ZERO;
}

//---------------------------------
//			初期化
//---------------------------------
void CPlayCamera::Init()
{
	//カメラの設定

	m_cameraPos = ZERO;						// カメラの位置
	m_tagetPos = ZERO;						//カメラの注視点
	m_upVec = { 0.0f,1.0f,0.0f };			// カメラ上方向
	m_rot = ZERO;							//カメラの回転値
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CPlayCamera::Step(VECTOR _vFocus, float _fRotY)
{
	//m_rot.y = _fRotY;

	//カメラ回転処理
	Rotate();


	//カメラの座標設定
	m_cameraPos.x = sinf(m_rot.y) * CAMERA_BACK;
	m_cameraPos.y = CAMERA_OFFSET_Y;
	m_cameraPos.z = cosf(m_rot.y) * CAMERA_BACK;

	m_cameraPos = VAdd(m_cameraPos, _vFocus);
	//=========================================

	m_tagetPos = _vFocus;
	m_tagetPos.y += TARGET_OFFSET_Y;

}

//---------------------------------
//			カメラの更新
//---------------------------------
void CPlayCamera::Update()
{
	// カメラ設定
	SetCameraPositionAndTargetAndUpVec(m_cameraPos, m_tagetPos, m_upVec);

}

//---------------------------------
//			カメラの回転処理
//---------------------------------
void CPlayCamera::Rotate()
{
	if (CheckHitKey(KEY_INPUT_LEFT) != 0)
	{
		m_rot.y += ROT_Y_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
	{
		m_rot.y -= ROT_Y_SPEED;
	}

}
