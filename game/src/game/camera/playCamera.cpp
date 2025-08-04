#include "PlayCamera.h"
#include <math.h>

//定義関連====================================
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const float CAMERA_BACK = 40.0f;				//カメラとプレイヤーの距離
static const float CAMERA_OFFSET_Y = 35.0f;			//カメラの修正Y
static const float TARGET_OFFSET_Y = 20.0f;			//ターゲットの修正Y
//============================================

//コンストラクタ
CPlayCamera::CPlayCamera() {
	m_cameraPos = ZERO;
	m_tagetPos = ZERO;
	m_upVec = ZERO;
	m_rot = ZERO;
}

//初期化
void CPlayCamera::Init()
{
	//カメラの設定

	m_cameraPos = ZERO;						// カメラの位置
	m_tagetPos = ZERO;						//カメラの注視点
	m_upVec = { 0.0f,1.0f,0.0f };			// カメラ上方向
	m_rot = ZERO;							//カメラの回転値
}

//毎フレームする処理
void CPlayCamera::Step(VECTOR _vFocus, float _fRotY)
{
	m_rot.y = _fRotY;
	//カメラの座標設定
	m_cameraPos.x = sinf(m_rot.y) * CAMERA_BACK;
	m_cameraPos.y = CAMERA_OFFSET_Y;
	m_cameraPos.z = cosf(m_rot.y) * CAMERA_BACK;

	m_cameraPos = VAdd(m_cameraPos, _vFocus);
	//=========================================

	m_tagetPos = _vFocus;
	m_tagetPos.y += TARGET_OFFSET_Y;


}

//カメラの更新
void CPlayCamera::Update()
{
	// カメラ設定
	SetCameraPositionAndTargetAndUpVec(m_cameraPos, m_tagetPos, m_upVec);

}

