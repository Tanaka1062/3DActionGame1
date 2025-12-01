#pragma once
#include "../../lib/model/3DObject.h"
#include "../player/playerData.h"

//敵のクラス
class CShotBase:public CObject
{
private:
	int m_lostTime;				//消える時間
	int m_timeCount;			//時間カウント
	int m_atk;					//攻撃力
	float m_moveSpeed;			//移動スピード
	int m_effectHndl;			//エフェクトのハンドル
	tagPlayerName m_shotName;	//誰が弾を出したか

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

	//終了処理
	void Exit();

	//呼び出し
	// _pos			:呼び出す座標
	// _rad			:半径
	// _rot			:打ち出す方向
	// _speed		:弾の速度
	// _atk			:攻撃力
	// _lostTime	:消えるまでの時間
	// _effectHndl	:弾のエフェクト
	void Request(VECTOR _pos,VECTOR _rot,float _rad,float _speed,int _atk,int _lostTime,
		tagPlayerName _name,int _effectHndl = -1);

	//攻撃力を取得
	int GetAtk() { return m_atk; }

	//弾を出しているキャラの名前を取得
	tagPlayerName GetShotName() { return m_shotName; }

private:

	//移動処理
	void Move();


};

