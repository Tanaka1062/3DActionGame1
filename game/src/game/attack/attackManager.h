#pragma once

#pragma once
#include <iostream>
#include <list>
#include"attackBase.h"

using namespace std;

//攻撃の当たり判定のマネージャーのクラス
class CAttackManager
{
private:
	list<CAttackBase*> m_attack;			//攻撃の当たり判定のクラス
public:
	//コンストラクタ・デストラクタ
	CAttackManager();
	~CAttackManager();

	//初期化
	void Init();
	//モデルロード
	void Load();
	//更新処理
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

	//攻撃の呼び出し
	// _pos			:呼び出す座標
	// _rad			:半径
	// _atk			:攻撃力
	// _attackType	:攻撃のタイプ
	// _num			:連続攻撃の回数
	// _nextTime	:連続攻撃の次の攻撃が発生するまでの時間
	void Request(VECTOR _pos, float _rad, int _atk, tagAttackType _attackType, int _num = 1,int _nextTime = 0);

	//攻撃の当たり判定の数を取得
	int GetNum() { return static_cast<int>(m_attack.size()); }

	//攻撃の当たり判定のアドレスを取得
	CAttackBase* GetAttack(int _num);

};

