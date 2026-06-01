#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <vector>
#include "../../../player/playerData.h"

class CResultPlayerPanel
{
private:
	VECTOR					m_pos;			//中心座標
	int						m_money;		//お金の量
	C2DObject				m_panel;		//パネル
	std::vector<int>		m_iconHndl;		//アイコンの画像ハンドル
	C2DObject				m_icon;			//アイコン
	int						m_playerMoney;	//プレイヤーのお金

public:
	//コンストラクタ・デストラクタ
	CResultPlayerPanel();
	~CResultPlayerPanel();

	//初期化
	void Init();

	//画像ロード
	void Load(tagPlayerName _playerName,VECTOR _pos,int _money);

	//描写処理
	void Draw();

	//終了処理
	void Exit();

};

