#pragma once
#include "../../lib/model/actor.h"

//敵のクラス
class CShotBase:public CActor
{
private:
	int m_lostTime;			//消える時間
	int m_timeCount;		//時間カウント
	int m_atk;				//攻撃力
	float m_moveSpeed;		//移動スピード
public:
	//コンストラクタ・デストラクタ
	CShotBase();
	~CShotBase();

	//初期化
	void Init();

	//モデルロード
	void Load(int _modelHndl);

	//毎フレームする処理
	void Step();

	//描写処理
	void Draw();

	//更新処理
	void Update();

	//呼び出し
	// _pos			:呼び出す座標
	// _rad			:半径
	// _rot			:打ち出す方向
	// _speed		:弾の速度
	// _atk			:攻撃力
	// _lostTime	:消えるまでの時間
	void Request(VECTOR _pos,VECTOR _rot,float _rad,float _speed,int _atk,int _lostTime);

	//攻撃力を取得
	int GetAtk() { return m_atk; }

private:

	//移動処理
	void Move();


};

