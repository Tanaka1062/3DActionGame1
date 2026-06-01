#pragma once
#include "../lib/2D/2DObject.h"

class CMapSelect
{
public:
	enum tagMapSelect
	{
		MAP_1,		//マップ1つ目
		MAP_2,		//マップ2つ目

		MAP_NUM,	//マップの数
	};

private:

	C2DObject		m_map[MAP_NUM];		//マップ
	int				m_nowMap;			//選択されているマップ
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

