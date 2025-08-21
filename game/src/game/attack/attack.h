#pragma once
#include "../../lib/model/3DObject.h"

//攻撃のクラス
class CAttack :public CObject
{
private:
	int m_time;				//攻撃判定の時間(フレーム)
	int m_timeCount;		//時間のカウント
	float m_length;			//攻撃の射程
	bool m_isAttackable;		//攻撃可能かどうか
public:
	//コンストラクタ
	CAttack();

	//初期化
	void Init(float _rad = 0.0f, float _length = 0.0f);

	//毎フレームする処理
	void Step();

	//更新処理
	//  _pos	:攻撃を出すオブジェクの座標
	//  _rot	:攻撃を出すオブジェクトの向き
	void Update(VECTOR _pos, VECTOR _rot);

	//攻撃の呼び出し
	//  _pos	:攻撃を出すオブジェクの座標
	//  _rot	:攻撃を出すオブジェクトの向き
	// _time	:攻撃判定の時間(フレーム)
	void Request(VECTOR _pos,VECTOR _rot,int _time);

	//攻撃可能範囲の半径を取得
	float GetAttackableRad() { return m_rad; };

	//攻撃可能かを取得
	bool GetIsAttackable() { return m_isAttackable; }
	//攻撃可能かを設定
	void SetIsAttackable(bool _isAttack) { m_isAttackable = _isAttack; }

};

