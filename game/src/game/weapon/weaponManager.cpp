#include "weaponManager.h"

static const char* MODEL_PATH[WEAPON_ID_NUM] ={		//ロードするファイル名
	"",
	"data/model/weapon/hammer/weapon_hammer.mv1",
	"data/model/weapon/ax/weapon_ax.mv1",
	"data/model/weapon/gun/weapon_gun.mv1",
};				

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
	int hndl[WEAPON_ID_NUM] = { -1 };

	//武器のモデルハンドルロード
	for (int weaponHnd_i = 0; weaponHnd_i < WEAPON_ID_NUM; weaponHnd_i++)
	{
		hndl[weaponHnd_i] = MV1LoadModel(MODEL_PATH[weaponHnd_i]);
	}

	//武器のクラスにモデルをコピー
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		for (int weaponHnd_i = 0; weaponHnd_i < WEAPON_ID_NUM; weaponHnd_i++)
		{
			m_weapon[player_i].Load(hndl[weaponHnd_i],weaponHnd_i);
		}

	}
}

//---------------------------
//	  毎フレームする処理
//---------------------------
void CWeaponManager::Step(CPlayerManager& _playerManager)
{
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		//武器を持っているかを保存
		bool isWeapon = false;
		//プレイヤーの武器のIDを取得
		tagWeaponId weaponId = _playerManager.GetPlayer(player_i)->GetWeaponId();
		tagState state = _playerManager.GetPlayer(player_i)->GetState();
		VECTOR playerPos = _playerManager.GetPlayer(player_i)->GetCenter();

		m_weapon[player_i].Step(weaponId,state,playerPos);
	}
}

//---------------------------
//		  更新処理
//---------------------------
void CWeaponManager::Update(CPlayerManager& _playerManager)
{
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		//プレイヤーのハンドルを取得
		int hndl = _playerManager.GetPlayer(player_i)->GetHndl();
		tagWeaponId weaponId = _playerManager.GetPlayer(player_i)->GetWeaponId();
		m_weapon[player_i].Update(hndl);
	}
}

//---------------------------
//		  描写処理
//---------------------------
void CWeaponManager::Draw()
{
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_weapon[player_i].Draw();
	}
}

//---------------------------
//		  終了処理
//---------------------------
void CWeaponManager::Exit()
{
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_weapon[player_i].Exit();
	}
}
