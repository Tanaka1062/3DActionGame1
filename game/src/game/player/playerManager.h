#pragma once
#include <iostream>
#include <vector>
#include "player.h"

using namespace std;

//エネミーマネージャーのクラス
class CPlayerManager
{
private:
	vector<CPlayer*> m_player;			//プレイヤーのクラス
	vector <int> m_modelHndl;			//モデルのハンドル
	CShotManager* m_shotManager;		//弾のマネージャー

public:
	//コンストラクタ・デストラクタ
	CPlayerManager();
	~CPlayerManager();

	//初期化
	void Init(CAttackManager* _attackManager = nullptr,
		CShotManager* _shotManager = nullptr);
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

	//プレイヤーの数を取得
	int GetPlayerNum() { return static_cast<int>(m_player.size()); }

	//プレイヤーを取得
	CPlayer* GetPlayer(int _num) { return m_player[_num]; }
};

