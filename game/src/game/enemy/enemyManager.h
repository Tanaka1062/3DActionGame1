#pragma once
#include <iostream>
#include <vector>
#include "enemy.h"

using namespace std;

//エネミーマネージャーのクラス
class CEnemyManager
{
private:
	vector<CEnemy*> m_enemy;			//敵のクラス

public:
	//コンストラクタ・デストラクタ
	CEnemyManager();
	~CEnemyManager();

	//初期化
	void Init();
	//オブジェクトのロード
	void Load();
	//毎フレームする処理
	void Step(VECTOR _pos);
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

	//敵の数を取得
	int GetEnemyNum() { return static_cast<int>(m_enemy.size()); }

	//敵を取得
	CEnemy* GetEnemy(int _num) { return m_enemy[_num]; }
};

