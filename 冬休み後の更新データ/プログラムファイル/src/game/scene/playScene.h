#pragma once
#include "sceneBase.h"
#include "../map/map.h"
#include "../sky/sky.h"
#include"../data.h"
#include"../character/characterBase.h"
#include "../shot/shotManager.h"
#include "../item/itemManager.h"
#include "../weapon/weaponManager.h"
#include "../attack/attackManager.h"
#include "../player/playerManager.h"
#include "../ui/uiGameManager.h"
#include "../gameTime/gameTime.h"
#include "../winner/winner.h"

//ゲーム本編を管理するクラス
class CPlayScene :public CSceneBase
{
private:

	CMap m_ground;							//背景
	CSky m_sky;								//空
	CPlayerManager m_playerManager;			//プレイヤー
	CShotManager m_shot;					//弾
	CItemManager m_itemManager;				//アイテムマネージャークラス
	CWeaponManager m_weaponManager;			//武器のマネージャークラス
	CAttackManager m_attackManager;			//攻撃のマネージャークラス
	CUiGameManager m_uiManager;				//uiのマネージャークラス
	CGameTime* m_gameTime;					//ゲームの制限時間
	CWinner* m_winner;						//勝利したプレイヤー

public:

	//コンストラクタ
	CPlayScene();
	//デストラクタ
	~CPlayScene();

	//描画処理
	void Draw();

private:

	//初期化
	void Init();

	//データ読み込み
	void Load();

	//メイン処理
	void Step();

	//終了前処理
	void Exit();

};

