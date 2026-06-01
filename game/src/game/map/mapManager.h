#pragma once
#include "mapBase.h"

enum tagMapId			//マップのID
{
	MAP_ID_NONE = -1,	//初期化用
	MAP_ID_GRASSLAND,	//草原ステージ
	MAP_ID_SELECT,		//選択画面のマップ
	MAP_ID_RESULT,		//リザルト画面のマップ
	MAP_ID_TITLE,		//タイトル画面のマップ

	MAP_NUM,			//マップの数
};

class CMapManager
{
private:
	CMapBase* m_map;	//マップ	
public:
	//コンストラクタ・デストラクタ
	CMapManager();
	~CMapManager();

	//初期化
	void Init(tagMapId _mapId);

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

	//更新処理
	void Update();

	//モデルの描写
	void Draw();

	//終了処理
	void Exit();

	//マップのアドレスを取得
	CMapBase* GetMap() { return m_map; }
};

