#include "weapon.h"
#include "../system/effectData/effectData.h"
#include "../../lib/effekseer/effekseer.h"

using namespace PlayerData;

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
	m_effectHndl = -1;
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
void CWeapon::Step(tagWeaponId _playerWeaponId,tagState _state,VECTOR _playerPos)
{
	//武器ごとにモデルのハンドルを変更する
	m_hndl = m_weaponHndl[_playerWeaponId];

	//斧を使っていたらエフェクトを呼び出す
	if (_playerWeaponId == WEAPON_ID_AX && _state == tagState::ATTACK)
	{
		if (m_effectHndl == -1)
		{
			int effectId = CEffectData::GetId(EFFECT_AX);

			m_effectHndl = CEffekseerCtrl::Request(effectId, _playerPos, false);
		}
		else
		{
			CEffekseerCtrl::SetPosition(m_effectHndl, _playerPos);

			if (CEffekseerCtrl::IsActive(m_effectHndl) == false)
			{
				m_effectHndl = -1;
			}
		}
	}

	//攻撃を止めたらエフェクトを止める
	if (m_effectHndl != -1 && _state != tagState::ATTACK)
	{
		CEffekseerCtrl::Stop(m_effectHndl);
		m_effectHndl = -1;
	}
}

//--------------
//   更新処理
//--------------
void CWeapon::Update(int _hndl)
{
	CObject::Update();

	MATRIX scale = MGetScale(VGet(0.1f, 0.1f, 0.1f));
	MATRIX rotY = MGetRotY(90.0f * DX_PI_F / 180.0f);
	MATRIX mat = MMult(scale, rotY);
	MATRIX world = MV1GetFrameLocalWorldMatrix(_hndl, 11);
	mat = MMult(mat, world);

	MV1SetMatrix(m_hndl, mat);
}

