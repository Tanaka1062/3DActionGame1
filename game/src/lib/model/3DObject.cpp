#include"3DObject.h"
#include "../../game/common.h"

static const float GRAVITIY = 0.3f;						//重力
static const float GRAVITIY_MAX = 5.0f;					//最大重力

//---------------------
//	コンストラクタ
//---------------------
CObject::CObject()
{
	Init();
}

//---------------------
//	デストラクタ
//---------------------
CObject::~CObject()
{
	Exit();
}

//---------------------
//		初期化
//---------------------
void CObject::Init()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_speed = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_scale = { 1.0f,1.0f,1.0f };
	m_hndl = -1;
	m_rad = 0.0f;
	m_gravity = 0.0f;
	m_isActive = true;
	m_isGravity = false;
}

//---------------------
//		終了処理
//---------------------
void CObject::Exit()
{
	DeleteModel();
}

//---------------------
//	毎フレームする処理
//---------------------
void CObject::Step()
{
	if (m_isGravity == true)
	{
		//重力処理
		Gravity();
	}
}

//---------------------
//		数値の更新
//---------------------
void CObject::Update()
{

	//重力を速度に加算
	m_speed.y -= m_gravity;

	//速度を制限
	if (m_speed.y <= -GRAVITIY_MAX)
	{
		m_speed.y = -GRAVITIY_MAX;
	}

	//現在の座標にスピードを加算
	m_pos = VAdd(m_pos, m_speed);


	MV1SetPosition(m_hndl, m_pos);
	MV1SetRotationXYZ(m_hndl, m_rot);
	MV1SetScale(m_hndl, m_scale);
}

//---------------------
//	オブジェクトの描写
//---------------------
void CObject::Draw()
{
	//Activeがfalseなら描画をしない
	if (m_isActive == false)return;

#ifdef DEBUG
	//当たり判定を表示
	DrawSphere3D(GetCenter(), m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
#endif // DEBUG

	MV1DrawModel(m_hndl);
}

//---------------------
//オブジェクトのロード
//---------------------
void CObject::Load()
{

}

//---------------------
//	モデルデータロード
//---------------------
bool CObject::LoadModel(const char* _filePath)
{
	if (m_hndl == -1)
	{
		m_hndl = MV1LoadModel(_filePath);
		return true;
	}
	return false;
}

//---------------------
//	モデルコピーロード
//---------------------
bool CObject::DuplicateModel(int _originHndl)
{
	if (m_hndl == -1)
	{
		m_hndl = MV1DuplicateModel(_originHndl);
		return true;
	}
	return false;
}

//---------------------
//	モデルデータ削除
//---------------------
void CObject::DeleteModel()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}

//------------------------------
//		当たり判定後の処理
//------------------------------
void CObject::HitCalc()
{

}

//------------------------------
//	オブジェクトを押し出す
//------------------------------
void CObject::ObjPush(VECTOR _push)
{
	//押し出す量をスピードに加算
	m_speed.x += _push.x;
	m_speed.y += _push.y;
	m_speed.z += _push.z;

}

//------------------------------
//			重力リセット
//------------------------------
void CObject::GravityReset()
{
	m_gravity = 0.0f;
	m_isFlying = false;
}

//------------------------------
//		中心座標を取得
//------------------------------
VECTOR CObject::GetCenter()
{
	VECTOR center = m_pos;
	center.y += m_rad;

	return center;
}

//-----------------------------
//		  速度のリセット
//------------------------------
void CObject::ResetSpeed()
{
	//スピードをリセット
	m_speed = { 0.0f,0.0f,0.0f };
}

//-----------------------------
//			重力処理
//-----------------------------
void CObject::Gravity()
{
	m_gravity += GRAVITIY;
}
