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
