#pragma once
#include <iostream>
#include <list>
#include "shotBase.h"

using namespace std;


//エネミーマネージャーのクラス
class CShotManager
{
private:
	list<CShotBase*> m_shot;			//弾のクラス
	int m_hndl;							//弾のモデルハンドル
public:
	//コンストラクタ・デストラクタ
	CShotManager();
	~CShotManager();

	//初期化
	void Init();
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

	//ショットの呼び出し
	// _pos			:呼び出す座標
	// _rot			:打ち出す方向
	// _rad			:半径
	// _speed		:弾の速度
	// _atk			:攻撃力
	// _lostTime	:消えるまでの時間
	// _effectHndl	:弾のエフェクト
	void Request(VECTOR _pos, VECTOR _rot,float _rad, float _speed, int _atk, int _lostTime,
				int _effectHndl = -1);

	//弾の数を取得
	int GetNum() { return static_cast<int>(m_shot.size());}

	//弾のアドレスを取得
	CShotBase* GetShot(int _num);

};

