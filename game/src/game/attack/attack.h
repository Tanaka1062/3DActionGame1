#pragma once
#include "../../lib/model/3DObject.h"

//攻撃のクラス
class CAttack :public CObject
{
private:
	int m_time;				//攻撃判定の時間(フレーム)
	int m_timeCount;		//時間のカウント
	float m_length;			//攻撃の射程
public:
	//コンストラクタ
	CAttack();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//更新処理
	//  _pos	:攻撃を出すオブジェクの座標
	//  _rot	:攻撃を出すオブジェクトの向き
	void Update(VECTOR _pos, VECTOR _rot);

	//攻撃の呼び出し
	//  _pos	:攻撃を出すオブジェクの座標
	//  _rot	:攻撃を出すオブジェクトの向き
	// _rad		:攻撃範囲の半径
	// _length	:オブジェクトからの射程距離
	// _time	:攻撃判定の時間(フレーム)
	void Request(VECTOR _pos,VECTOR _rot,float _rad,float _length,int _time);

};

