#include"3DObject.h"

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
	m_isActive = true;
}

//---------------------
//		終了処理
//---------------------
void CObject::Exit()
{
	DeleteModel();
}

//---------------------
//		数値の更新
//---------------------
void CObject::Update()
{
	//現在の座標にスピードを加算
	m_pos = VAdd(m_pos, m_speed);

	//スピードをリセット
	m_speed = { 0.0f,0.0f,0.0f };

	MV1SetPosition(m_hndl, m_pos);
	MV1SetRotationXYZ(m_hndl, m_rot);
	MV1SetScale(m_hndl, m_scale);
}

//---------------------
//	オブジェクトの描写
//---------------------
void CObject::Draw()
{
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
//		中心座標を取得
//------------------------------
VECTOR CObject::GetCenter()
{
	VECTOR center = m_pos;
	center.y += m_rad;

	return center;
}
