#pragma once
#include "../../lib/model/3DObject.h"

//視界範囲のクラス
class CFOV :public CObject
{
private:
	int m_time;					//当たったかが消えるまでの時間(フレーム)
	int m_timeCount;			//時間のカウント
	bool m_isHit;				//当たったか
public:
	//コンストラクタ
	CFOV();

	//初期化
	void Init(float _rad);

	//毎フレームする処理
	void Step();

	//更新処理
	//  _pos	:攻撃を出すオブジェクの座標
	void Update(VECTOR _pos);

	//当たり判定後の処理
	void HitCalc();

	//当たったかを取得
	bool GetHit() { return m_isHit; }

};

