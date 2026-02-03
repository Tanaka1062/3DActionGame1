#include "weaponManager.h"

static const char MODEL_PATH[] =
{ "data/model/weapon/weapon.mv1" };				//ロードするファイル名

//---------------------------
//		 コンストラクタ
//---------------------------
CWeaponManager::CWeaponManager()
{
	Init();
}

//---------------------------
//		  デストラクタ
//---------------------------
CWeaponManager::~CWeaponManager()
{
	Exit();
}

//---------------------------
//			初期化
//---------------------------
void CWeaponManager::Init()
{
	for (int i = 0; i < PAD_NUM; i++)
	{
		m_weapon[i].Init();
	}
}

//---------------------------
//		  モデルロード
//---------------------------
void CWeaponManager::Load()
{
	//武器のモデルハンドルロード
	int hndl = MV1LoadModel(MODEL_PATH);

	for (int i = 0; i < PAD_NUM; i++)
	{
		m_weapon[i].Load(hndl);
	}
}

//---------------------------
//	  毎フレームする処理
//---------------------------
void CWeaponManager::Step(CPlayerManager& _playerManager)
{
	for (int i = 0; i < PAD_NUM; i++)
	{
		//武器を持っているかを保存
		bool isWeapon = false;
		//プレイヤーの武器のIDを取得
		tagWeaponId weaponId = _playerManager.GetPlayer(i)->GetWeaponId();

		//武器が素手以外の場合武器を持っているフラグをtrue
		if (weaponId != WEAPON_ID_HAND)
		{
			isWeapon = true;
		}

		m_weapon[i].Step(isWeapon);
	}
}

//---------------------------
//		  更新処理
//---------------------------
void CWeaponManager::Update(CPlayerManager& _playerManager)
{
	for (int i = 0; i < PAD_NUM; i++)
	{
		//プレイヤーのハンドルを取得
		int hndl = _playerManager.GetPlayer(i)->GetHndl();
		m_weapon[i].Update(hndl);
	}
}

//---------------------------
//		  描写処理
//---------------------------
void CWeaponManager::Draw()
{
	for (int i = 0; i < PAD_NUM; i++)
	{
		m_weapon[i].Draw();
	}
}

//---------------------------
//		  終了処理
//---------------------------
void CWeaponManager::Exit()
{
	for (int i = 0; i < PAD_NUM; i++)
	{
		m_weapon[i].Exit();
	}
}
