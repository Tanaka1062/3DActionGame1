#pragma once
#include"../../lib/model/3DObject.h"

//武器のクラス
class CWeapon : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CWeapon();
	~CWeapon();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//更新処理
	void Update(int _hndl);

};

