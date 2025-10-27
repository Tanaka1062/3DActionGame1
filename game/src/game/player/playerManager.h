#pragma once
#include <iostream>
#include <vector>
#include "player.h"

enum tagModelId
{
	PLAYER_MODEL_ID_A,		//モデルIDA
	PLAYER_MODEL_ID_B,		//モデルIDB

	PLAYER_MODEL_ID_NUM,	//モデルIDの数
};

using namespace std;

//エネミーマネージャーのクラス
class CPlayerManager
{
private:
	vector<CPlayer*> m_player;				//敵のクラス
	int m_modelHndl[PLAYER_MODEL_ID_NUM];	//モデルのハンドル

public:
	//コンストラクタ・デストラクタ
	CPlayerManager();
	~CPlayerManager();

	//初期化
	void Init(CAttackManager* _attackManager = nullptr);
	//オブジェクトのロード
	void Load();
	//毎フレームする処理
	void Step(float _rot);
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

	//敵の数を取得
	int GetEnemyNum() { return static_cast<int>(m_player.size()); }

	//敵が全部死んだかを取得
	bool GetIsAllDie() {
		int num = 0;
		for (int i = 0; i < m_player.size(); i++)
		{
			if (m_player[i]->GetActive() == false)
			{
				num++;
			}
		}
		if (num == m_player.size())
		{
			return true;
		}
		return false;
	};

	//敵を取得
	CPlayer* GetPlayer(int _num) { return m_player[_num]; }
};

