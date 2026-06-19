#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <array>
#include "../../player/playerData.h"
#include "../../player/player.h"

class CPlayerStatusPanel
{
private:
	//アイコンの状態
	enum tagIconState
	{
		ICON_NORMAL,							//ノーマルアイコン
		ICON_STAGGER,							//怯みアイコン
		ICON_DIE,								//死亡アイコン
		ICON_ATTACK,							//攻撃アイコン

		ICON_STATE_NUM,							//アイコンの状態の数
	};

	//ハートの状態
	enum tagHeartState
	{
		HEART_EMPTY,							//空
		HEART_QUARTER,							//4分の1
		HEART_HALF,								//半分
		HEART_THREE_QUARTER,					//4分の3
		HEART_FULL,								//満タン

		HEART_STATE_NUM,						//ハートの状態の数
	};

	static constexpr int HEART_NUM = 8;					//ハートの数

	VECTOR								m_pos;			//中心座標
	int									m_money;		//お金の量
	C2DObject							m_panel;		//パネル
	std::array<int, ICON_STATE_NUM>		m_iconHndl;		//アイコンの画像ハンドル
	C2DObject							m_icon;			//アイコン
	std::array<int, HEART_STATE_NUM>	m_heartHndl;	//ハートの画像ハンドル			
	std::array<C2DObject,HEART_NUM>		m_heart;		//ハート
	int									m_playerMoney;	//プレイヤーのお金

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

