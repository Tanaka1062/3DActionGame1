#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"

//マップのID
enum tagMapId
{
	MAP_ID_GRASSLAND,			//草原ステージ
	MAP_ID_SELECT,				//選択画面のマップ
	MAP_ID_RESULT,				//リザルト画面のマップ

	MAP_NUM,					//マップの数
};

//マップの中心ID
enum tagMapCenterId
{
	MAP_ID_CENTER_NONE = -1,	//ID無し
	MAP_ID_CENTER1,				//中心一つ目
	MAP_ID_CENTER2,				//中心二つ目
	MAP_ID_CENTER3,				//中心三つ目
	MAP_ID_CENTER4,				//中心四つ目
	MAP_ID_CENTER5,				//中心五つ目

	MAP_CENTER_NUM,				//中心の数
};

static const char* MAP_FRAME_PATH[MAP_NUM] = {
	"data/model/map/TestMap8Frame.mv1",
	"data/model/map/selectMap/selectMapFrame.mv1",
	"data/model/map/resultMap/resultMapFrame.mv1",
};					//マップのフレームパス



class CMap :public CObject
{
private:
	int m_hitHndl;			//当たり判定ようのマップのハンドル
	int  m_mapId;			//マップのID
	int m_mapMoveTimer;		//マップの移動する時間
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

	//当たり判定ようのマップのハンドルを取得
	int GetHitHndl() { return m_hitHndl; }

	//マップのIDを取得
	tagMapCenterId GetCenterId() { return static_cast<tagMapCenterId>(m_mapId); }

};

