#pragma once
#include "../lib/2D/2DObject.h"
#include "../../map/playMap/playMapData.h"

class CMapSelect
{
public:
	enum tagArrow
	{
		LEFT,
		RIGHT,

		ARROW_NUM,
	};
private:
	C2DObject		m_map[playMap::MAP_NUM];		//マップ
	float			m_mapScale[playMap::MAP_NUM];	//マップの大きさ
	C2DObject		m_frame[playMap::MAP_NUM];		//フレーム
	int				m_nowMap;						//選択されているマップ
	bool			m_isMove;						//移動フラグ
	C2DObject		m_arrow[ARROW_NUM];				//矢印
	C2DObject		m_text;							//テキスト
	C2DObject		m_mapText[playMap::MAP_NUM];	//マップテキスト
	float			m_mapTextScale;					//マップテキストの大きさ
	bool			m_isMapSelect;					//マップ選択フラグ
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

	//マップ選択フラグ取得
	bool GetIsMapSelect() { return m_isMapSelect; }
};

