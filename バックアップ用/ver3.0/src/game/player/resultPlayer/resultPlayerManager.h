#pragma once
#include <iostream>
#include <vector>
#include "resultPlayer.h"

//エネミーマネージャーのクラス
class CResultPlayerManager
{
private:
	std::vector<CResultPlayer*> m_player;			//プレイヤーのクラス
	std::vector <int> m_modelHndl;			//モデルのハンドル
	std::vector <VECTOR>m_spawnPos;			//プレイヤーの出現座標
public:
	//コンストラクタ・デストラクタ
	CResultPlayerManager();
	~CResultPlayerManager();

	//初期化
	void Init(tagPlayerName _winPlayer);
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

	//プレイヤーの数を取得
	int GetPlayerNum() { return static_cast<int>(m_player.size()); }

	//プレイヤーを取得
	CPlayer* GetPlayer(int _num) { return m_player[_num]; }

};

