#include "mapCamera.h"
#include <math.h>
#include "../../map/map.h"

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化

constexpr float MOVE_SPEED = 0.5f;				//カメラの移動速度

//============================================

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
	int frameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_GRASSLAND]);

	m_pos = MV1GetFramePosition(frameHndl,1);

	int frameNum = 4;
	for (int mapCenter_i = 0; mapCenter_i < MAP_CENTER_NUM; mapCenter_i++)
	{
		m_mapCenterPos[mapCenter_i] = MV1GetFramePosition(frameHndl, frameNum);

		frameNum += 2;
	}

	m_focusPos = m_mapCenterPos[0];

	m_pos.x = m_pos.x - 50.0f;

}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CMapCamera::Step(VECTOR _focus, float _rot, tagMapCenterId _mapCenterId)
{
	//カメラの方向ベクトルを基にY軸回転角度を計算
	VECTOR dir = VSub(m_pos, m_focusPos);
	m_rot.y = atan2f(dir.x, dir.z);

	Move(_mapCenterId);

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
void CMapCamera::Move(tagMapCenterId _mapCenterId)
{
	if (m_focusPos.z > m_mapCenterPos[_mapCenterId].z)
	{
		m_focusPos.z -= MOVE_SPEED;
		m_pos.z -= MOVE_SPEED;
	}
	else
	{
		m_focusPos.z = m_mapCenterPos[_mapCenterId].z;
		m_pos.z = m_mapCenterPos[_mapCenterId].z;
	}
}

