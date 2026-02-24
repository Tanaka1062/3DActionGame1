#pragma once
#include "../../lib/2DUi/2DUi.h"
#include <iostream>
#include <vector>
#include "../../player/playerData.h"
#include "../../player/player.h"

class CPlayerStatusPanel
{
private:
	VECTOR m_pos;							//中心座標
	int m_money;							//お金の量
	C2DUi m_panel;							//パネル	
	C2DUi m_icon;							//アイコン
	std::vector<int>m_heartHndl;			//ハートの画像ハンドル			
	std::vector<C2DUi*>m_heart;				//ハート

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

