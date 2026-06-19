#pragma once
#include "../player/playerManager.h"
#include "weapon.h"
#include <iostream>
#include <array>

//武器のマネージャークラス
class CWeaponManager
{
private:
	std::array<CWeapon, PLAYER_NUM> m_weapon;		//武器
public:
	//コンストラクタ・デストラクタ
	CWeaponManager();
	~CWeaponManager();

	//初期化
	void Init();
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step(CPlayerManager& _playerManager);
	//更新処理
	void Update(CPlayerManager& _playerManager);
	//描写処理
	void Draw();
	//終了処理
	void Exit();

};

