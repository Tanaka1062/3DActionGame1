#pragma once
#include <iostream>
#include <vector>
#include "shotBase.h"

using namespace std;


//エネミーマネージャーのクラス
class CShotManager
{
private:
	vector<CShotBase*> m_shot;			//弾のクラス

public:
	//コンストラクタ・デストラクタ
	CShotManager();
	~CShotManager();

	//初期化
	void Init();
	//オブジェクトのロード
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
	// _speed		:弾の速度
	// _atk			:攻撃力
	// _lostTime	:消えるまでの時間
	void Request(VECTOR _pos, VECTOR _rot, VECTOR _speed, int _atk, int _lostTime);

};

