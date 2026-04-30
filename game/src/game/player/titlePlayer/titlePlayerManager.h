#pragma once
#include <iostream>
#include <vector>
#include "titlePlayer.h"
#include "../../winner/winner.h"
#include "../../map/mapBase.h"

//エネミーマネージャーのクラス
class CTitlePlayerManager
{
private:
	std::vector<CTitlePlayer*>	m_player;		//プレイヤーのクラス
	std::vector <int>			m_modelHndl;	//モデルのハンドル
	std::vector<int>			m_materialHndl;	//マテリアルのハンドル
	std::vector <VECTOR>		m_spawnPos;		//プレイヤーの出現座標
public:
	//コンストラクタ・デストラクタ
	CTitlePlayerManager();
	~CTitlePlayerManager();

	//初期化
	void Init();
	//オブジェクトのロード
	void Load(CMapBase* _map);
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

