#include "mapCamera.h"
#include <math.h>

//定義関連====================================
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr float CAMERA_OFFSET_Y = 10.0f;			//カメラの修正Y
constexpr float TARGET_OFFSET_Y = 2.0f;			//ターゲットの修正Y

constexpr float MAX_LEN_NEAR = 30.0f;			//この距離より離れるとカメラ移動開始
constexpr float MAX_LEN_FAR = 35.0f;				//これ以上は離させない
constexpr float MIN_LEN_NEAR = 25.0f;			//この距離より近づくとカメラ移動開始
constexpr float MIN_LEN_FAR = 20.0f;				//これ以上は近づけさせない
constexpr float CAMERA_MOVE_SPEED = 0.5f;		//カメラのデフォルト移動速度
constexpr float CAMERA_ROT_SPEED = 2.0f;			//カメラの回転速度
//============================================

constexpr const char POS_PATH[] =
 "data/model/map/TestMap4FramePos.mv1" ;			//ロードするファイル名

//---------------------------------
//		コンストラクタ
//---------------------------------
CMapCamera::CMapCamera() {
	Init(ZERO);
}

//---------------------------------
//			初期化
//---------------------------------
void CMapCamera::Init(VECTOR _focus)
{
	CCameraBase::Init(ZERO);
	m_focusPos = ZERO;

	//フレームのハンドルをロード
	int frameHndl = MV1LoadModel(POS_PATH);

	m_pos = MV1GetFramePosition(frameHndl,9);
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CMapCamera::Step(VECTOR _focus, float _rot)
{
	//カメラの方向ベクトルを基にY軸回転角度を計算
	VECTOR dir = VSub(m_pos, m_focusPos);
	m_rot.y = atan2f(dir.x, dir.z);

}

//---------------------------------
//		カメラの更新
//---------------------------------
void CMapCamera::Update()
{

	// カメラ設定更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_focusPos, m_upVec);

}

//---------------------------------
//		カメラの回転処理
//---------------------------------
void CMapCamera::Rotate(VECTOR _focus)
{

}

//---------------------------------
//		 カメラの移動処理
//---------------------------------
void CMapCamera::Move(VECTOR _focus, float _rot)
{

}

