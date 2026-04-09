#include "selectCamera.h"
#include <math.h>

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR INIT_POS = { -123.0f,35.0f,0.0f };
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CSelectCamera::CSelectCamera() {
	Init(nullptr);
}

//---------------------------------
//			初期化
//---------------------------------
void CSelectCamera::Init(CMapBase* _map)
{
	CCameraBase::Init(_map);
	m_pos = INIT_POS;
	m_focusPos = _map->GetStagePos(0);

}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CSelectCamera::Step(int _hndl)
{
	//カメラの方向ベクトルを基にY軸回転角度を計算
	VECTOR dir = VSub(m_pos, m_focusPos);
	m_rot.y = atan2f(dir.x, dir.z);

}

//---------------------------------
//		カメラの更新
//---------------------------------
void CSelectCamera::Update()
{

	// カメラ設定更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_focusPos, m_upVec);

}

//---------------------------------
//		カメラの回転処理
//---------------------------------
void CSelectCamera::Rotate(VECTOR _focus)
{

}

//---------------------------------
//		 カメラの移動処理
//---------------------------------
void CSelectCamera::Move(VECTOR _focus, float _rot)
{

}

