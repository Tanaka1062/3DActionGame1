#include "cameraBase.h"

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const VECTOR CAMERA_UP = { 0.0f,1.0f,0.0f };	//カメラの上方向

//コンストラクタ
CCameraBase::CCameraBase()
{
	Init();
}

//初期化
void CCameraBase::Init()
{
	m_pos = ZERO;
	m_rot = ZERO;
	m_upVec = CAMERA_UP;
}

//毎フレームする処理
void CCameraBase::Step()
{

}

//カメラの更新
void CCameraBase::Update()
{

}

