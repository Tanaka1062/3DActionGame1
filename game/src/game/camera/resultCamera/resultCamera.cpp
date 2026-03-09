#include "resultCamera.h"
#include <math.h>

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR INIT_POS = { -50.0f,40.0f,0.0f };
constexpr VECTOR FOCUS_POS = { 0.0f,30.0f,0.0f };
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CResultCamera::CResultCamera() {
	Init(nullptr);
}

//---------------------------------
//			初期化
//---------------------------------
void CResultCamera::Init(CMapBase* _map)
{
	CCameraBase::Init(_map);
	m_pos = INIT_POS;
	m_focusPos = FOCUS_POS;

}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CResultCamera::Step(VECTOR _focus, float _rot)
{
	//カメラの方向ベクトルを基にY軸回転角度を計算
	VECTOR dir = VSub(m_pos, m_focusPos);
	m_rot.y = atan2f(dir.x, dir.z);

}

//---------------------------------
//		カメラの更新
//---------------------------------
void CResultCamera::Update()
{

	// カメラ設定更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_focusPos, m_upVec);

}

//---------------------------------
//		カメラの回転処理
//---------------------------------
void CResultCamera::Rotate(VECTOR _focus)
{

}

//---------------------------------
//		 カメラの移動処理
//---------------------------------
void CResultCamera::Move(VECTOR _focus, float _rot)
{

}

