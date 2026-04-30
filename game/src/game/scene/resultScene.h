#pragma once
#include "sceneBase.h"
#include <DxLib.h>
#include "../winner/winner.h"
#include "../sky/sky.h"
#include "../map/mapManager.h"
#include "../player/resultPlayer/resultPlayerManager.h"
#include "../../lib/2D/2DObject.h"

//ゲーム本編を管理するクラス
class CResultScene :public CSceneBase
{
private:
	CWinner*				m_winner;				//勝利したプレイヤー
	CSky					m_sky;					//天球
	CMapManager				m_mapManager;			//マップ
	CResultPlayerManager	m_resultPlayerManager;	//リザルトプレイヤー
	C2DObject				m_winPlayerText;		//勝利したプレイヤーのテキスト
	C2DObject				m_resultText;			//リザルト画面に表示されるテキスト
public:

	//コンストラクタ
	CResultScene();
	//デストラクタ
	~CResultScene();

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

