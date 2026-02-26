#include "mapCamera.h"
#include <math.h>
#include "../../map/map.h"

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };					//VECTOR用初期化

constexpr float MOVE_SPEED = 0.8f;							//カメラの移動速度

constexpr int MAP_FRAME_NUM = 4;							//マップのフレーム番号

constexpr VECTOR CAMERA_LENGTH = { 100.0f,0.0f,0.0f };		//カメラとプレイヤーの距離
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

	m_basePos = ZERO;

	//フレームのハンドルをロード
	int mapFrameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_GRASSLAND]);

	m_pos = MV1GetFramePosition(mapFrameHndl,1);
	m_basePos = m_pos;
	m_basePos.z = 0.0f;

	int frameNum = MAP_FRAME_NUM;
	for (int mapCenter_i = 0; mapCenter_i < MAP_CENTER_NUM; mapCenter_i++)
	{
		m_mapCenterPos[mapCenter_i] = MV1GetFramePosition(mapFrameHndl, frameNum);

		frameNum += 2;
	}

	///マップのフレームを削除
	if (mapFrameHndl != -1)
	{
		MV1DeleteModel(mapFrameHndl);
	}

	m_focusPos = m_mapCenterPos[0];

	//m_pos.x = m_pos.x - 100.0f;

	//m_pos.y = m_pos.y - 30.0f;
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CMapCamera::Step(VECTOR _focus, float _rot, tagMapCenterId _mapCenterId, VECTOR _playerPos)
{
	//カメラの方向ベクトルを基にY軸回転角度を計算
	VECTOR dir = VSub(m_pos, m_focusPos);
	m_rot.y = atan2f(dir.x, dir.z);

	Move(_mapCenterId);

	//注視点からプレイヤーの角度を求める
	float angle = atan2f(_playerPos.x - _focus.x, _playerPos.z - _focus.z);

	//角度を行列に変換する
	MATRIX rot = MGetRotY(angle);

	//ベースの座標と角度を合体させる
	VECTOR offset = VTransform(m_basePos, rot);

	//カメラの注視点からベース
	m_pos = VAdd(CAMERA_LENGTH,offset);

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

	//カメラの注視点を次のマップに移動させる
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

