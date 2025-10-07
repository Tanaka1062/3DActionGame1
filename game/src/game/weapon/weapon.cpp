#include "weapon.h"

static const char MODEL_PATH[] =
{ "data/model/weapon/weapon.mv1" };				//ロードするファイル名

//--------------
//コンストラクタ
//--------------
CWeapon::CWeapon()
{
	Init();
}

//--------------
//デストラクタ
//--------------
CWeapon::~CWeapon()
{
	CObject::Exit();
}

//--------------
//	  初期化
//--------------
void CWeapon::Init()
{
	CObject::Init();

}

//--------------
// モデルロード
//--------------
void CWeapon::Load()
{
	CObject::LoadModel(MODEL_PATH);
}

//--------------
//毎フレームする処理
//--------------
void CWeapon::Step(int _hndl, VECTOR _pos)
{
	MATRIX world = MV1GetFrameLocalWorldMatrix(_hndl, 15);
	MATRIX rotX = MGetRotX(0.0f);
	MATRIX rotY = MGetRotY(0.0f);
	MATRIX rotZ = MGetRotZ(0.0f);
	MATRIX mat = MGetTranslate(_pos);
	mat = MMult(mat, world);
	m_pos.x = mat.m[3][0];
	m_pos.y = mat.m[3][1];
	m_pos.z = mat.m[3][2];
}

