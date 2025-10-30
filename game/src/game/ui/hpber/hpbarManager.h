#pragma once
#include "hpbar.h"
#include "../../player/playerManager.h"

//HPバーのマネージャー
class CHpbarManager
{
private:
	CHpbar m_hpbar[PLAYER_NUM];			//HPバー
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

