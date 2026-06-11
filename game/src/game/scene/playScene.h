#pragma once
#include "sceneBase.h"
#include "../map/mapManager.h"
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
#include "../ranking/ranking.h"
#include "../event/eventManager.h"
#include "../3DUi/3DUiManager.h"

//ゲーム本編を管理するクラス
class CPlayScene :public CSceneBase
{
private:

	CMapManager		m_mapManager;		//マップ
	CSky			m_sky;				//空
	CPlayerManager	m_playerManager;	//プレイヤー
	CShotManager	m_shot;				//弾
	CItemManager	m_itemManager;		//アイテムマネージャークラス
	CWeaponManager	m_weaponManager;	//武器のマネージャークラス
	CAttackManager*	m_attackManager;	//攻撃のマネージャークラス
	CUiGameManager	m_uiManager;		//uiのマネージャークラス
	CGameTime*		m_gameTime;			//ゲームの制限時間
	CRanking*		m_ranking;			//プレイヤーの順位
	CEventManager	m_eventManager;		//イベントのマネージャークラス
	C3DUiManager*	m_3DUiManager;		//3DUIのマネージャークラス

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

