#include "cameraBase.h"

constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR CAMERA_UP = { 0.0f,1.0f,0.0f };	//カメラの上方向

//コンストラクタ
CCameraBase::CCameraBase()
{
	Init(ZERO);
}

//初期化
void CCameraBase::Init(VECTOR _focus)
{
	m_pos = ZERO;
	m_rot = ZERO;
	m_upVec = CAMERA_UP;

}

//毎フレームする処理
void CCameraBase::Step(VECTOR _focus, float _rot)
{

}

//カメラの更新
void CCameraBase::Update()
{

}

