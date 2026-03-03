#include "mapCamera.h"
#include <math.h>
#include "../../map/map.h"

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };					//VECTOR用初期化

constexpr float MOVE_SPEED = 0.6f;							//カメラの移動速度

constexpr int MAP_FRAME_NUM = 4;							//マップのフレーム番号

constexpr float CAMERA_LENGTH =  -120.0f;					//カメラとプレイヤーの距離

constexpr float ROT_SPEED = 0.2f * (DX_PI_F / 180.0f);		//カメラの回転スピード

constexpr float ROT_Y_MAX = 30.0f * (DX_PI_F / 180.0f);		//カメラの最大のY軸回転角度

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
	m_nextPos = ZERO;
	m_nextFocus = ZERO;

	//フレームのハンドルをロード
	int mapFrameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_GRASSLAND]);

	m_pos = MV1GetFramePosition(mapFrameHndl,1);
	m_basePos = m_pos;
	m_basePos.z = 0.0f;
	m_basePos.x -= 80.0f;

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

	m_state = ZOOM_CAMERA;

	m_mapCenterId = MAP_ID_CENTER_NONE;
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CMapCamera::Step(VECTOR _focus, float _rot, tagMapCenterId _mapCenterId, CPlayerManager* _playerManager)
{
	if (m_mapCenterId != _mapCenterId)
	{
		m_state = MAP_MOVE_CAMERA;
		m_mapCenterId = _mapCenterId;
	}

	Move(_mapCenterId,_playerManager);

	m_rot.y = atan2f(m_pos.x - m_focusPos.x, m_pos.z - m_focusPos.z);

	//カメラの注視点からベース
	m_nextPos = VAdd(m_focusPos, m_basePos);

	VECTOR vec = VSub(m_nextPos, m_pos);

	if (vec.x > 3.0f)
	{
		m_pos.x += MOVE_SPEED;
	}
	else if (vec.x < -3.0f)
	{
		m_pos.x -= MOVE_SPEED;
	}

	if (vec.z > 3.0f)
	{
		m_pos.z += MOVE_SPEED;
	}
	else if(vec.z < -3.0f)
	{
		m_pos.z -= MOVE_SPEED;
	}

	VECTOR vec2 = VSub(m_nextFocus, m_focusPos);

	if (vec2.x > 3.0f)
	{
		m_focusPos.x += MOVE_SPEED;
	}
	else if (vec2.x < -3.0f)
	{
		m_focusPos.x -= MOVE_SPEED;
	}

	if (vec2.z > 3.0f)
	{
		m_focusPos.z += MOVE_SPEED;
	}
	else if (vec2.z < -3.0f)
	{
		m_focusPos.z -= MOVE_SPEED;
	}

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
void CMapCamera::Move(tagMapCenterId _mapCenterId,CPlayerManager* _playerManager)
{

	//カメラの注視点を次のマップに移動させる
	if (m_focusPos.z > m_mapCenterPos[_mapCenterId].z &&m_state == MAP_MOVE_CAMERA)
	{
		m_nextFocus.z -= MOVE_SPEED;
		m_nextPos.x = m_basePos.x;
	}
	else
	{
		m_state = ZOOM_CAMERA;

		float minX = 0.0f;
		float maxX = 0.0f;
		float minZ = 0.0f;
		float maxZ = 0.0f;

		for (int player_i = 0; player_i < _playerManager->GetPlayerNum(); player_i++)
		{
			CPlayer* player = _playerManager->GetPlayer(player_i);
			VECTOR vec = player->GetPos();
			//それぞれの最大X,Zと最小X,Z
			if (minX > vec.x || minX == 0.0f)
			{
				minX = vec.x;
			}
			if (maxX < vec.x || maxX == 0.0f)
			{
				maxX = vec.x;
			}
			if (minZ > vec.z || minZ == 0.0f)
			{
				minZ = vec.z;
			}
			if (maxZ < vec.z || maxZ == 0.0f)
			{
				maxZ = vec.z;
			}
		}

		//中央をカメラの注視点にする
		m_nextFocus.x = (minX + maxX) / 2.0f;
		m_nextFocus.z = (maxZ + minZ) / 2.0f;

	}
}

