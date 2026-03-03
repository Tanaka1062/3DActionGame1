#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"
#include <iostream>
#include <vector>

//マップのID
enum tagMapId
{
	MAP_ID_GRASSLAND,	//草原ステージ
	MAP_ID_SELECT,		//選択画面のマップ
	MAP_ID_RESULT,		//リザルト画面のマップ

	MAP_NUM,			//マップの数
};

//ステージのID
enum tagStageId
{
	STAGE_ID_NONE = -1,	//ID無し
	STAGE_ID_1,			//ステージ一つ目
	STAGE_ID_2,			//ステージ二つ目
	STAGE_ID_3,			//ステージ三つ目
	STAGE_ID_4,			//ステージ四つ目
	STAGE_ID_5,			//ステージ五つ目

	STAGE_NUM,			//ステージの数
};

static const char* MAP_FRAME_PATH[MAP_NUM] = {
	"data/model/map/TestMap9Frame.mv1",
	"data/model/map/selectMap/selectMapFrame.mv1",
	"data/model/map/resultMap/resultMapFrame.mv1",
};					//マップのフレームパス


class CMap
{
private:
	std::vector<CObject*>	m_stage;
	int						m_hitHndl;		//当たり判定ようのマップのハンドル
	int						m_mapId;		//マップのID
	int						m_mapMoveTimer;	//マップの移動する時間
public:
	//コンストラクタ・デストラクタ
	CMap();
	~CMap();


	//初期化
	void Init();

	//モデルロード
	void Load(tagMapId _id);

	//毎フレームする処理
	void Step();

	//モデル描写
	void Draw();

	//終了処理
	void Exit();

	//当たり判定ようのマップのハンドルを取得
	int GetHitHndl() { return m_hitHndl; }

	//マップのIDを取得
	tagMapCenterId GetCenterId() { return static_cast<tagMapCenterId>(m_mapId); }

};

