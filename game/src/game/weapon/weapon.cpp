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
	for (int weaponHndl_i = 0; weaponHndl_i < WEAPON_ID_NUM; weaponHndl_i++)
	{
		m_weaponHndl[weaponHndl_i] = -1;
	}
}

//--------------
// モデルロード
//--------------
void CWeapon::Load(int _hndl, int _weaponId)
{
	m_weaponHndl[_weaponId] = MV1DuplicateModel(_hndl);
}

//--------------
//毎フレームする処理
//--------------
void CWeapon::Step(tagWeaponId _playerWeaponId)
{
	//武器ごとにモデルのハンドルを変更する
	m_hndl = m_weaponHndl[_playerWeaponId];
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

