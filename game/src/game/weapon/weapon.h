#pragma once
#include"../../lib/model/3DObject.h"

//武器のクラス
class CWeapon : public CObject
{
private:
public:
	//コンストラクタ・デストラクタ
	CWeapon();
	~CWeapon();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step(int _hndl,VECTOR _pos);

};

