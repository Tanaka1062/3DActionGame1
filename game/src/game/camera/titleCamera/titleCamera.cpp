#include "titleCamera.h"
#include <math.h>

//定義関連====================================
constexpr VECTOR	ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr int		MAP_FRAME_NUM = 2;				//マップのフレーム番号
constexpr VECTOR	FOCUS_POS = { 0.0f,30.0f,0.0f };
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CTitleCamera::CTitleCamera() {
	Init(nullptr);
}

//---------------------------------
//			初期化
//---------------------------------
void CTitleCamera::Init(CMapBase* _map)
{
	CCameraBase::Init(_map);

	if (_map == nullptr)return;

	m_focusPos = _map->GetStagePos(0);

}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CTitleCamera::Step(int _hndl)
{
	//カメラの方向ベクトルを基にY軸回転角度を計算
	VECTOR dir = VSub(m_pos, m_focusPos);
	m_rot.y = atan2f(dir.x, dir.z);

	m_pos = MV1GetFramePosition(_hndl, MAP_FRAME_NUM);

}

//---------------------------------
//		カメラの更新
//---------------------------------
void CTitleCamera::Update()
{

	// カメラ設定更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_focusPos, m_upVec);

}

//---------------------------------
//		カメラの回転処理
//---------------------------------
void CTitleCamera::Rotate(VECTOR _focus)
{

}

//---------------------------------
//		 カメラの移動処理
//---------------------------------
void CTitleCamera::Move(VECTOR _focus, float _rot)
{

}

