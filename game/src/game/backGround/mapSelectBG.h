#pragma once
#include "../lib/2D/2DObject.h"
#include <iostream>
#include <vector>
#include "../map/playMap/playMapData.h"

class CMapSelectBG
{
private:
	std::vector<int>	m_bgHndl[playMap::MAP_NUM];		//背景の画像ハンドル
	int					m_bgId;							//背景のID
	C2DObject			m_bg;							//背景
public:
	//コンストラクタ・デストラクタ
	CMapSelectBG();
	~CMapSelectBG();

	//初期化
	void Init();

	//画像ロード
	void Load();

	//毎フレームする処理
	void Step();

	//画像描写
	void Draw();

	//終了処理
	void Exit();
};

