#pragma once

#pragma once
#include <iostream>
#include <vector>
#include"attackBase.h"
#include "../player/playerData.h"

//攻撃の当たり判定のマネージャーのクラス
class CAttackManager
{
private:
	static std::vector<CAttackBase*> m_attack;			//攻撃の当たり判定のクラス
public:
	//コンストラクタ・デストラクタ
	CAttackManager();
	~CAttackManager();

	//初期化
	static void Init();
	//更新処理
	static void Update();
	//オブジェクトの描写
	static void Draw();
	//終了処理
	static void Exit();

	//攻撃の呼び出し
	// _pos			:呼び出す座標
	// _rad			:半径
	// _atk			:攻撃力
	// _blown		:吹き飛び量
	// _name		:攻撃するキャラの名前
	// _num			:連続攻撃の回数
	// _nextTime	:連続攻撃の次の攻撃が発生するまでの時間
	static int Request(VECTOR _pos, float _rad, int _atk, int _blown,tagPlayerName _name, int _num = 1,int _nextTime = 0);

	//攻撃の当たり判定の数を取得
	static int GetNum() { return static_cast<int>(m_attack.size()); }

	//攻撃の当たり判定のアドレスを取得
	static CAttackBase* GetAttack(int _num);

	//攻撃の座標を設定する
	static void SetPos(int _num,VECTOR _pos);

	//攻撃の生存フラグを取得
	static bool GetActive(int _num);
};

