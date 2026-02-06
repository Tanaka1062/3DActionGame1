#include "resultCamera.h"
#include <math.h>
#include "../../map/map.h"

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CResultCamera::CResultCamera() {
	Init(ZERO);
}

//---------------------------------
//			初期化
//---------------------------------
void CResultCamera::Init(VECTOR _focus)
{
	CCameraBase::Init(ZERO);
	m_focusPos = ZERO;

	//フレームのハンドルをロード
	int mapFrameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_RESULT]);

	m_pos = MV1GetFramePosition(mapFrameHndl,5);
	m_focusPos = MV1GetFramePosition(mapFrameHndl, 1);

	///マップのフレームを削除
	if (mapFrameHndl != -1)
	{
		MV1DeleteModel(mapFrameHndl);
	}

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

