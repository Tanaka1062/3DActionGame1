#pragma once
#include <iostream>
#include <vector>
#include "enemyBase.h"

using namespace std;

//エネミーマネージャーのクラス
class CEnemyManager
{
private:
	vector<CEnemyBase*> m_enemy;			//敵のクラス
	int m_rootHndl;							//移動ルートのハンドル
	int m_modelHndl;						//モデルのハンドル

public:
	//コンストラクタ・デストラクタ
	CEnemyManager();
	~CEnemyManager();

	//初期化
	void Init(CAttackManager* _attackManager = nullptr);
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

	//敵が全部死んだかを取得
	bool GetIsAllDie() {
		int num = 0;
		for (int i = 0; i < m_enemy.size(); i++)
		{
			if (m_enemy[i]->GetActive() == false)
			{
				num++;
			}
		}
		if (num == m_enemy.size())
		{
			return true;
		}
		return false;
	};

	//敵を取得
	CEnemyBase* GetEnemy(int _num) { return m_enemy[_num]; }
};

