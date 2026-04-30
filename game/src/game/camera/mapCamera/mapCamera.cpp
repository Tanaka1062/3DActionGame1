#include "mapCamera.h"
#include <math.h>
#include "../../map/mapBase.h"

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };					//VECTOR用初期化
constexpr VECTOR INIT_POS = { -300.0f,70.0f,0.0f };
constexpr float MAP_MOVE_SPEED = 1.2f;						//マップ移動用カメラの移動速度
constexpr float ZOOM_MOVE_SPEED = 0.4f;						//ズームカメラの移動速度
constexpr int MAP_FRAME_NUM = 4;							//マップのフレーム番号

constexpr float CAMERA_LENGTH =  -120.0f;					//カメラとプレイヤーの距離

constexpr float ROT_SPEED = 0.2f * (DX_PI_F / 180.0f);		//カメラの回転スピード

constexpr float ROT_Y_MAX = 30.0f * (DX_PI_F / 180.0f);		//カメラの最大のY軸回転角度
constexpr float OFFSET_X = -190.0f;							//カメラと注視点の引く距離
constexpr float MAX_Z = 50.0f;								//最大Z
constexpr float MAX_X = 25.0f;								//最大X
constexpr float CAMERA_FOLLOW_THRESHOLD = 5.0f;				//カメラの追従までの値
constexpr float MAX_Z_DISTANCE = 200.0f;					//Z方向の最大距離
constexpr float Z_DISTANCE_RATIO = 0.5f;					//Z方向の距離の割合
constexpr float MIN_Z_DISTANCE = 80.0f;						//Z方向の最小距離
constexpr float MIN_X_DISTANCE = 130.0f;					//X方向の最小距離
constexpr int NEXT_POS_WAIT_TIME = 30;						//次の座標を更新する時間
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CMapCamera::CMapCamera() {
	Init(nullptr);
}

//---------------------------------
//		 デストラクタ
//---------------------------------
CMapCamera::~CMapCamera() {
	Exit();
}

//---------------------------------
//			初期化
//---------------------------------
void CMapCamera::Init(CMapBase* _map)
{
	CCameraBase::Init(nullptr);

	m_focusPos = ZERO;
	m_basePos = ZERO;
	m_nextPos = ZERO;
	m_nextFocus = ZERO;

	m_pos = INIT_POS;
	m_basePos = m_pos;

	m_state = ZOOM_CAMERA;

	m_stageCenterId = 0;

	if (_map == nullptr)return;

	for (int stage_i = 0; stage_i < _map->GetStageNum(); stage_i++)
	{
		m_stageCenterPos.push_back(_map->GetStagePos(stage_i));
	}

	m_focusPos = m_stageCenterPos[0];

	m_nextPosTime = 0;
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CMapCamera::Step(int _stageCenterId, CPlayerManager* _playerManager)
{
	//現在のステージの中心が本来のステージの中心と違ったら変更する
	if (m_stageCenterId != _stageCenterId)
	{
		m_state = MAP_MOVE_CAMERA;
		m_stageCenterId = _stageCenterId;
	}

	//カメラを動かす処理
	Move(_stageCenterId,_playerManager);

	//注視点をステージの中心から離れすぎないように調整する--------------------------------
	if (m_nextFocus.z >= m_stageCenterPos[_stageCenterId].z + MAX_Z)
	{
		m_nextFocus.z = m_stageCenterPos[_stageCenterId].z + MAX_Z;
	}
	else if (m_nextFocus.z <= m_stageCenterPos[_stageCenterId].z - MAX_Z)
	{
		m_nextFocus.z = m_stageCenterPos[_stageCenterId].z - MAX_Z;
	}

	if (m_nextFocus.x <= m_stageCenterPos[_stageCenterId].x - MAX_X)
	{
		m_nextFocus.x = m_stageCenterPos[_stageCenterId].x - MAX_X;
	}
	//------------------------------------------------------------------------------------

	//カメラから注視点の方向をまとめる
	m_rot.y = atan2f(m_pos.x - m_focusPos.x, m_pos.z - m_focusPos.z);

	//本来いるべき座標を決められた時間に更新する
	if (m_nextPosTime >= NEXT_POS_WAIT_TIME)
	{
		//カメラの注視点からベース
		m_nextPos = VAdd(m_focusPos, m_basePos);
		m_nextPosTime = 0;
	}
	m_nextPosTime++;

	//カメラを本来いるべき座標に移動させる--------------------------
	VECTOR vec = VSub(m_nextPos, m_pos);
	if (vec.x > CAMERA_FOLLOW_THRESHOLD)
	{
		m_pos.x += MAP_MOVE_SPEED;
	}
	else if (vec.x < -CAMERA_FOLLOW_THRESHOLD)
	{
		m_pos.x -= MAP_MOVE_SPEED;
	}

	if (vec.z > CAMERA_FOLLOW_THRESHOLD)
	{
		m_pos.z += MAP_MOVE_SPEED;
	}
	else if(vec.z < -CAMERA_FOLLOW_THRESHOLD)
	{
		m_pos.z -= MAP_MOVE_SPEED;
	}
	//--------------------------------------------------------------

	//注視点を本来いるべき座標に移動させる--------------------------
	VECTOR vec2 = VSub(m_nextFocus, m_focusPos);
	if (vec2.x > CAMERA_FOLLOW_THRESHOLD)
	{
		m_focusPos.x += MAP_MOVE_SPEED;
	}
	else if (vec2.x < -CAMERA_FOLLOW_THRESHOLD)
	{
		m_focusPos.x -= MAP_MOVE_SPEED;
	}
	if (vec2.z > CAMERA_FOLLOW_THRESHOLD)
	{
		m_focusPos.z += MAP_MOVE_SPEED;
	}
	else if (vec2.z < -CAMERA_FOLLOW_THRESHOLD)
	{
		m_focusPos.z -= MAP_MOVE_SPEED;
	}
	//--------------------------------------------------------------

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
//		   カメラの終了処理
//---------------------------------
void CMapCamera::Exit()
{
	//ステージの中心座標を全て消す
	m_stageCenterPos.clear();
}

//---------------------------------
//カメラが移動しているかを取得
//---------------------------------
bool CMapCamera::GetIsMove()
{
	if (m_state == MAP_MOVE_CAMERA)
	{
		return true;
	}

	return false;
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
void CMapCamera::Move(int _stageCenterId,CPlayerManager* _playerManager)
{
	if (_playerManager == nullptr)return;

	//カメラの注視点を次のマップに移動させる
	if (m_focusPos.z > m_stageCenterPos[_stageCenterId].z &&m_state == MAP_MOVE_CAMERA)
	{
		m_nextFocus.z -= MAP_MOVE_SPEED;
		m_basePos.x = INIT_POS.x;
		m_nextPos.x = m_basePos.x;
	}
	//カメラをプレイヤーの位置を参考に移動させる
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
			if (player->GetActive() == false)continue;
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

		//Zの距離を求める
		float DistanceZ = maxZ - minZ;
		//最大距離以上離れていたらカメラを引く
		if (DistanceZ >= MAX_Z_DISTANCE)
		{
			m_basePos.x = OFFSET_X - DistanceZ * Z_DISTANCE_RATIO;
		}
		//最小距離以下ならカメラを近づける
		else if(DistanceZ <= MIN_Z_DISTANCE)
		{
			m_basePos.x = OFFSET_X + DistanceZ * Z_DISTANCE_RATIO;
		}
		//一番手前がカメラに近かったらカメラを引く
		if (minX - m_basePos.x <= MIN_X_DISTANCE)
		{
			m_basePos.x = minX - MIN_X_DISTANCE;
		}
		//中央をカメラの注視点にする
		m_nextFocus.x = (minX + maxX) / 2.0f;
		m_nextFocus.z = (maxZ + minZ) / 2.0f;

	}
}

