#include "PlayCamera.h"
#include <math.h>
#include"../../lib/input/keyInput.h"
#include"../../lib/input/controllerInput.h"

//定義関連====================================
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const float CAMERA_BACK = 25.0f;				//カメラとプレイヤーの距離
static const float CAMERA_OFFSET_Y = 18.5f;			//カメラの修正Y
static const float TARGET_OFFSET_Y = 5.0f;			//ターゲットの修正Y
static const float ROT_Y_SPEED = 0.1f;				//カメラのY軸回転スピード
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CPlayCamera::CPlayCamera() {
	Init();
}

//---------------------------------
//			初期化
//---------------------------------
void CPlayCamera::Init()
{
	CCameraBase::Init();
	m_tagetPos = ZERO;						//カメラの注視点
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CPlayCamera::Step()
{
	//カメラ回転処理
	Rotate();
}

//---------------------------------
//			カメラの更新
//---------------------------------
void CPlayCamera::Update(VECTOR _pos)
{
	//カメラの座標設定
	m_pos.x = sinf(m_rot.y) * CAMERA_BACK;
	m_pos.y = CAMERA_OFFSET_Y;
	m_pos.z = cosf(m_rot.y) * CAMERA_BACK;

	m_pos = VAdd(m_pos, _pos);
	//=========================================

	m_tagetPos = _pos;
	m_tagetPos.y += TARGET_OFFSET_Y;

	// カメラ設定更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_tagetPos, m_upVec);

}

//---------------------------------
//			カメラの回転処理
//---------------------------------
void CPlayCamera::Rotate()
{
	//コントローラー用カメラ回転
	if (CControllerInput::GetRX() != 0)
	{
		//スティックを入力した力分だけ回転する
		m_rot.y += ROT_Y_SPEED * CControllerInput::GetRX();
	}
	//キーボード用左回転
	else if (CheckHitKey(KEY_INPUT_LEFT) != 0)
	{
		m_rot.y -= ROT_Y_SPEED;
	}
	//キーボード用右回転
	else if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
	{
		m_rot.y += ROT_Y_SPEED;
	}

}
