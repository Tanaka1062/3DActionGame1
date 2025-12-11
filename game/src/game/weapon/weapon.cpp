#include "weapon.h"


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
void CWeapon::Load(int _hndl)
{
	CObject::DuplicateModel(_hndl);
}

//--------------
//毎フレームする処理
//--------------
void CWeapon::Step(bool _isWeapon)
{
	//武器を持っていたら武器を表示する
	if (_isWeapon)
	{
		m_isActive = true;
	}
	else
	{
		m_isActive = false;
	}
}

//--------------
//   更新処理
//--------------
void CWeapon::Update(int _hndl)
{
	CObject::Update();

	MATRIX scale = MGetScale(VGet(0.1f, 0.1f, 0.1f));
	MATRIX rotZ = MGetRotZ(0.0f * DX_PI_F / 180.0f);
	MATRIX mat = MMult(scale, rotZ);
	MATRIX world = MV1GetFrameLocalWorldMatrix(_hndl, 11);
	 mat = MMult(mat, world);

	MV1SetMatrix(m_hndl, mat);

}

