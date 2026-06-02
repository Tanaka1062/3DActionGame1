#pragma once
#include "../lib/2D/2DObject.h"
#include "../../map/playMap/playMapData.h"

class CMapSelect
{
private:
	C2DObject		m_map[playMap::MAP_NUM];		//マップ
	float			m_mapScale[playMap::MAP_NUM];	//マップの大きさ
	int				m_nowMap;						//選択されているマップ
	bool			m_isMove;						//移動フラグ
public:
	//コンストラクタ・デストラクタ
	CMapSelect();
	~CMapSelect();

	//初期化
	void Init();

	//画像ロード
	void Load();

	//毎フレームする処理
	void Step();

	//描写処理
	void Drow();

	//終了処理
	void Exit();

};

