#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <vector>
#include "../../player/playerData.h"
#include "../../player/player.h"

class CPlayerStatusPanel
{
private:
	VECTOR					m_pos;			//中心座標
	int						m_money;		//お金の量
	C2DObject				m_panel;		//パネル
	std::vector<int>		m_iconHndl;		//アイコンの画像ハンドル
	C2DObject				m_icon;			//アイコン
	std::vector<int>		m_heartHndl;	//ハートの画像ハンドル			
	std::vector<C2DObject*>	m_heart;		//ハート
	int						m_playerMoney;	//プレイヤーのお金

public:
	//コンストラクタ・デストラクタ
	CPlayerStatusPanel();
	~CPlayerStatusPanel();

	//初期化
	void Init();

	//画像ロード
	void Load(tagPlayerName _playerName);

	//毎フレームする処理
	void Step(CPlayer* _player);

	//描写処理
	void Draw();

	//終了処理
	void Exit();

};

