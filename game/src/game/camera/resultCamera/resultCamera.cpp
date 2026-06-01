#include "resultCamera.h"
#include <math.h>
#include "../../map/resultMap/resultMap.h"
#include "../../map/mapManager.h"

//定義関連====================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };			//VECTOR用初期化
constexpr VECTOR INIT_POS = { -60.0f,40.0f,0.0f };	//カメラの初期座標
constexpr float CAMERA_OFFSET_Y = 10.0f;			//注視点からカメラがどれだけ上にあるか
constexpr VECTOR FOCUS_POS = { 0.0f,30.0f,0.0f };	//注視点の初期座標
constexpr float FOCUS_MAX_Y = 300.0f;				//注視点の最大の高さ
constexpr float FOCUS_UP_SPEED = 1.5f;				//注視点の上昇スピード
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CResultCamera::CResultCamera() {
	Init(nullptr);
}

//---------------------------------
//			初期化
//---------------------------------
void CResultCamera::Init(CMapBase* _map)
{
	if (_map == nullptr)return;

	CCameraBase::Init(_map);
	m_pos = INIT_POS;
	m_focusPos = FOCUS_POS;
	m_mapBase = _map;
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CResultCamera::Step(int _hndl)
{
	if (m_mapBase->GetMapId() == MAP_ID_RESULT)
	{
		CResultMap* resultMap = dynamic_cast<CResultMap*>(m_mapBase);

		if (resultMap->GetIsPodiumAllMoveEnd() == true)
		{
			m_focusPos.y = FOCUS_MAX_Y;
		}
	}

	//注視点を最大の高さまで上昇させる
	if (m_focusPos.y < FOCUS_MAX_Y)
	{
		m_focusPos.y += FOCUS_UP_SPEED;
	}
	else
	{
		m_focusPos.y = FOCUS_MAX_Y;
	}
	//カメラの座標を注視点より上にする
	m_pos.y = m_focusPos.y + CAMERA_OFFSET_Y;
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

