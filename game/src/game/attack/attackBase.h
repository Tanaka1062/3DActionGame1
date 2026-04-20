#pragma once
#include "../../lib/model/3DObject.h"
#include "../player/playerData.h"

//攻撃のクラス
class CAttackBase :public CObject
{
private:
	bool			m_isAttack;			//攻撃しているかフラグ
	int				m_atk;				//攻撃力
	int				m_blown;			//吹っ飛び蓄積量
	int				m_num;				//攻撃の回数
	int				m_numCount;			//攻撃の回数カウント
	int				m_nextTime;			//攻撃の発生するまでの時間
	int				m_timeCount;		//時間のカウント
	tagPlayerName	m_attackName;		//攻撃しているプレイヤー

public:
	//コンストラクタ
	CAttackBase();

	//初期化
	void Init();

	//オブジェクトの描写
	void Draw();

	//更新処理
	void Update();

	//攻撃の呼び出し
	// _pos			:呼び出す座標
	// _rad			:半径
	// _atk			:攻撃力
	// _blown		:吹き飛び量
	// _name		:攻撃しているキャラの名前
	// _num			:連続攻撃の回数
	// _attackTime	:連続攻撃の経過時間
	void Request(VECTOR _pos, float _rad, int _atk,int _blown, tagPlayerName _name,int _num = 1, int _attackTime = 0);

	//攻撃力を取得
	int GetAtk() { return m_atk; }

	//吹き飛び量を取得
	int GetBlown() { return m_blown; }

	//攻撃可能かを取得
	bool GetIsAttack() { return m_isAttack; }

	//攻撃しているキャラの名前を取得
	tagPlayerName GetAttackName() { return m_attackName; }

	int GetNum() { return m_num; }

	int GetNumCount() { return m_numCount; }
};

