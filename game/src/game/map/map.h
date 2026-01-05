#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"

//マップのID
enum tagMapId
{
	MAP_ID_GRASSLAND,		//草原ステージ
	MAP_ID_SELECT,			//選択画面のマップ
	MAP_ID_RESULT,			//リザルト画面のマップ

	MAP_NUM,				//マップの数
};


class CMap :public CObject
{
private:
	int m_hitHndl;		//当たり判定ようのマップのハンドル
public:
	//コンストラクタ・デストラクタ
	CMap();
	~CMap();


	//初期化
	void Init();

	//モデルロード
	void Load(tagMapId _id);

	//モデル描写
	void Draw();

	//当たり判定ようのマップのハンドルを取得
	int GetHitHndl() { return m_hitHndl; }
};

