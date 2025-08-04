#pragma once

#include<DxLib.h>
#include "enemy.h"
#include <vector>

using namespace std;


class CEnemyManager
{
private:
	vector<CEnemy> m_enemy;		//敵
	int m_waitCount;			//敵が出るまでの時間
	int m_effectId;				//エフェクトのID

public:
	//コンストラクタ
	CEnemyManager();


	//初期化
	void Init();
	//ロード
	void Load();
	//毎フレームする処理
	void Step();
	//描写
	void Draw();
	//終了処理
	void Exit();


	//座標更新
	void Update();

	//敵をリクエスト
	void Request();

	//敵一体の情報取得
	CEnemy& GetEnemy(int _id) { return m_enemy[_id]; }

	//敵の数を取得
	int GetNum() { return static_cast<int>(m_enemy.size()); }
};


