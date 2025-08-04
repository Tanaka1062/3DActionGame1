#include "3DActor.h"

//---------------------------
//	コンストラクタ
//---------------------------
C3DActor::C3DActor()
{
	Init();
}

//---------------------------
//	デストラクタ
//---------------------------
C3DActor::~C3DActor()
{
	Exit();
}

//---------------------------
//	初期化
//---------------------------
void C3DActor::Init()
{

}

//---------------------------
//	ロード
//---------------------------
void C3DActor::Load()
{

}

//---------------------------
//	毎フレームする処理
//---------------------------
void C3DActor::Step()
{

}

//---------------------------
//			描写
//---------------------------
void C3DActor::Draw()
{
	if (m_isActive == false)return;

	MV1DrawModel(m_hndl);


#ifdef DEBUG

	//当たり判定を目視できるように
	DrawSphere3D(GetCenter(), m_radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG

}

//---------------------------
//			破棄
//---------------------------
void C3DActor::Exit()
{
	Delete();
}

//---------------------------
//		データ関連の破棄
//---------------------------
void C3DActor::Delete()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}

}


//---------------------------
//		座標,回転値更新
//---------------------------
void C3DActor::Update()
{
	//回転値セット
	MV1SetRotationXYZ(m_hndl, m_rot);

	//大きさセット
	MV1SetScale(m_hndl, m_scale);

	//座標セット
	MV1SetPosition(m_hndl, m_pos);

}

//当たり判定の座標用
VECTOR C3DActor::GetCenter()
{
	VECTOR res = m_pos;
	res.y += m_radius;

	return res;
}

//当たり判定後の処理
void C3DActor::HitCalc()
{
	m_isActive = false;
}
