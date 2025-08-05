#pragma once
#include "../character/characterBase.h"



class CPlayer:public CCharacterBase
{
private:

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

private:
	//待機処理
	void Wait();

	//歩く処理
	void Walk();

	//ジャンプ
	void Jump();

	//攻撃
	void Attack();

	//怯み
	void Stagger();

};

