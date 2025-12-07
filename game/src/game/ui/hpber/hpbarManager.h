#pragma once
#include "hpbar.h"
#include "../../player/playerManager.h"
#include "../../lib/2DUi/2DUi.h"


//HPバーのマネージャー
class CHpbarManager
{
private:
	CHpbar m_hpbar[PLAYER_NUM];			//HPバー
	enum tagUiName
	{
		PLAYER1_NAME_UI,
		PLAYER2_NAME_UI,
		PLAYER3_NAME_UI,
		PLAYER4_NAME_UI,
		VS_UI,

		UI_NUM,
	};

	C2DUi m_ui[UI_NUM];						//UI
public:
	//コンストラクタ・デストラクタ
	CHpbarManager();
	~CHpbarManager();

	//初期化
	void Init(CPlayerManager* _playerManager = nullptr);
	//ロード
	void Load();
	//毎フレームする処理
	void Step();
	//描写
	void Draw();
	//破棄
	void Exit();

};

