#pragma once
#include <iostream>
#include <vector>
#include "player.h"

//エネミーマネージャーのクラス
class CPlayerManager
{
private:
	std::vector<CPlayer*> m_player;			//プレイヤーのクラス
	std::vector <int> m_modelHndl;			//モデルのハンドル
	std::vector <VECTOR>m_spawnPos;			//プレイヤーの出現座標

public:
	//コンストラクタ・デストラクタ
	CPlayerManager();
	~CPlayerManager();

	//初期化
	void Init();
	//オブジェクトのロード
	void Load();
	//毎フレームする処理
	void Step(CAttackManager* _attackManager,CShotManager* _shotManager,float _rot);
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

	//ゲームが終わったかを取得
	bool GetIsEnd();

};

