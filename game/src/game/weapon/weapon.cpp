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
//   更新処理
//--------------
void CWeapon::Update(int _hndl)
{
	CObject::Update();

	MATRIX scale = MGetScale(VGet(0.2f, 0.1f, 0.1f));
	//MATRIX rotX = MGetRotX(-120.0f * DX_PI_F / 180.0f);
	//MATRIX rotY = MGetRotY(0.0f * DX_PI_F / 180.0f);
	MATRIX rotZ = MGetRotZ(90.0f * DX_PI_F / 180.0f);
	MATRIX mat = MMult(scale, rotZ);
	MATRIX world = MV1GetFrameLocalWorldMatrix(_hndl, 15);
	 mat = MMult(mat, world);

	MV1SetMatrix(m_hndl, mat);

}

