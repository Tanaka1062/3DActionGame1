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
void CWeapon::Init(int _hndl)
{
	CObject::Init();
	m_playerHndl = _hndl;

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
void CWeapon::Step()
{
	MATRIX size = MGetScale(VGet(1.0f, 1.0f, 1.0f));
	MATRIX rotX = MGetRotX(0.0f);
	MATRIX rotY = MGetRotY(0.0f);
	MATRIX rotZ = MGetRotZ(0.0f);
	

}

