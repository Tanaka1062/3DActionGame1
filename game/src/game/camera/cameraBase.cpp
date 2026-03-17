#include "cameraBase.h"

constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };			//VECTOR用初期化
constexpr VECTOR CAMERA_UP = { 0.0f,1.0f,0.0f };	//カメラの上方向
constexpr float DECELERATION = 0.9f;				//減速度

//コンストラクタ
CCameraBase::CCameraBase()
{
	Init(nullptr);
}

//デストラクタ
CCameraBase::~CCameraBase()
{
	Exit();
}

//初期化
void CCameraBase::Init(CMapBase* _map)
{
	m_pos = ZERO;
	m_speed = ZERO;
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

//カメラの終了処理
void CCameraBase::Exit()
{

}

//座標に速度を加算する
void CCameraBase::UpdataSpeed()
{
	m_pos = VAdd(m_pos, m_speed);

	m_speed = VScale(m_speed, DECELERATION);
}

