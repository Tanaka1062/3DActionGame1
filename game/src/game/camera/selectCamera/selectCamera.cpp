#include "selectCamera.h"
#include <math.h>

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
//============================================

static const char POS_PATH[] =
 "data/model/map/selectMap/SelectMapFrame.mv1" ;			//ロードするファイル名

//---------------------------------
//		コンストラクタ
//---------------------------------
CSelectCamera::CSelectCamera() {
	Init(ZERO);
}

//---------------------------------
//			初期化
//---------------------------------
void CSelectCamera::Init(VECTOR _focus)
{
	CCameraBase::Init(ZERO);
	m_focusPos = ZERO;

	//フレームのハンドルをロード
	int frameHndl = MV1LoadModel(POS_PATH);

	m_pos = MV1GetFramePosition(frameHndl,5);
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CSelectCamera::Step(VECTOR _focus, float _rot)
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

