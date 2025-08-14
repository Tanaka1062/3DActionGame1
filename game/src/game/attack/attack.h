#pragma once
#include "../../lib/model/3DObject.h"

//攻撃のクラス
class CAttack :public CObject
{
private:
	int m_time;				//攻撃判定の時間(フレーム)
	int m_timeCount;		//時間のカウント
public:
	//コンストラクタ
	CAttack();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//攻撃の呼び出し
	//　_obj	:攻撃を出すオブジェクト
	// _rad		:攻撃範囲の半径
	// _length	:オブジェクトからの射程距離
	// _time	:攻撃判定の時間(フレーム)
	void Request(const CObject& _obj,float _rad,float _length,int _time);

};

