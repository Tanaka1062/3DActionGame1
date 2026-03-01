#include "mapCamera.h"
#include <math.h>
#include "../../map/map.h"

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };					//VECTOR用初期化

constexpr float MOVE_SPEED = 0.8f;							//カメラの移動速度

constexpr int MAP_FRAME_NUM = 4;							//マップのフレーム番号

constexpr float CAMERA_LENGTH =  -120.0f;					//カメラとプレイヤーの距離

constexpr float ROT_SPEED = 0.5f * (DX_PI_F / 180.0f);		//カメラの回転スピード

constexpr float ROT_Y_MAX = 45.0f * (DX_PI_F / 180.0f);		//カメラの最大のY軸回転角度
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

	m_pos.x = m_pos.x - 50.0f;

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

	float len = m_pos.x - _playerPos.x;

	//if (len > CAMERA_LENGTH)
	//{
	//	m_pos.x -= MOVE_SPEED;
	//	m_focusPos.x -= MOVE_SPEED;
	//}
	//else if (len < CAMERA_LENGTH)
	//{
	//	m_pos.x += MOVE_SPEED;
	//	m_focusPos.x += MOVE_SPEED;
	//}

	//注視点からプレイヤーの角度を求める
	float angle1 = atan2f(_playerPos.x - m_focusPos.x, _playerPos.z - m_focusPos.z);
	float angle2 = atan2f(m_pos.x - m_focusPos.x, m_pos.z - m_focusPos.z);
	
	float diff = angle1 - angle2;

	if (fabs(diff) > 0.05f)
	{

		while (diff > DX_PI_F)
		{
			diff -= DX_TWO_PI_F;
		}
		while (diff < -DX_PI_F)
		{
			diff += DX_TWO_PI_F;
		}

		if (diff < ROT_SPEED)
		{
			diff = ROT_SPEED;
		}
		else if (diff > -ROT_SPEED)
		{
			diff = -ROT_SPEED;
		}

		m_rot.y += diff;

		if (m_rot.y > ROT_Y_MAX)
		{
			m_rot.y = ROT_Y_MAX;
		}
		else if (m_rot.y < -ROT_Y_MAX)
		{
			m_rot.y = -ROT_Y_MAX;
		}
	}

	//角度を行列に変換する
	MATRIX rot = MGetRotY(m_rot.y);

	//ベースの座標と角度を合体させる
	VECTOR offset = VTransform(m_basePos, rot);

	//カメラの注視点からベース
	m_pos = VAdd(m_focusPos,offset);

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
		//m_basePos.z -= MOVE_SPEED;
		//m_pos.z -= MOVE_SPEED;
	}
	else
	{
		m_focusPos.z = m_mapCenterPos[_mapCenterId].z;
	
	}
}

