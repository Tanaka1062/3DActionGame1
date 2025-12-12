#pragma once
#include"../../lib/model/3DObject.h"
#include"../player/player.h"

//武器のクラス
class CWeapon : public CObject
{
private:
	int m_weaponHndl[WEAPON_ID_NUM];	//武器のモデルハンドル保存用
public:
	//コンストラクタ・デストラクタ
	CWeapon();
	~CWeapon();

	//初期化
	void Init();

	//モデルロード
	void Load(int _hndl,int _weaponId);

	//毎フレームする処理
	void Step(tagWeaponId _playerWeaponId);

	//更新処理
	void Update(int _hndl);

};

