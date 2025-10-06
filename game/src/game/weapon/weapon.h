#pragma once
#include"../../lib/model/3DObject.h"

//武器のクラス
class CWeapon : public CObject
{
private:
	int m_playerHndl;		//プレイヤーのモデルハンドル
public:
	//コンストラクタ・デストラクタ
	CWeapon();
	~CWeapon();

	//初期化
	void Init(int _hndl = -1);

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

};

