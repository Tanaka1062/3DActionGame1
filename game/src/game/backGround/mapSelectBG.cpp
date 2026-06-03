#include "mapSelectBG.h"
#include "../data.h"

using namespace std;
namespace
{
	constexpr int BG_NUM[playMap::MAP_NUM] =		//背景の画像の数
	{
		5,
		5,
	};

	constexpr VECTOR INIT_POS =						//初期座標
	{ WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y,0.0f };

	vector<const char*> BG_GRAPHIC_PATH[playMap::MAP_NUM] =
	{
		{
			"data/graphic/mapSelect/grassland/stage1.png",
			"data/graphic/mapSelect/grassland/stage2.png",
			"data/graphic/mapSelect/grassland/stage3.png",
			"data/graphic/mapSelect/grassland/stage4.png",
			"data/graphic/mapSelect/grassland/stage5.png",
		},

		{
			"data/graphic/mapSelect/grassland/stage1.png",
			"data/graphic/mapSelect/grassland/stage2.png",
			"data/graphic/mapSelect/grassland/stage3.png",
			"data/graphic/mapSelect/grassland/stage4.png",
			"data/graphic/mapSelect/grassland/stage5.png",
		},
	};
}

//---------------------------
//	   コンストラクタ
//---------------------------
CMapSelectBG::CMapSelectBG()
{
	for (int playMap_i = 0; playMap_i < playMap::MAP_NUM; playMap_i++)
	{
		for (int bg_i = 0; bg_i < BG_NUM[playMap_i]; bg_i++) 
		{
			m_bgHndl[playMap_i].push_back(-1);
		}
	}

	Init();
}

//---------------------------
//		 デストラクタ
//---------------------------
CMapSelectBG::~CMapSelectBG()
{
	Exit();
}

//---------------------------
//			初期化
//---------------------------
void CMapSelectBG::Init()
{
	for (int playMap_i = 0; playMap_i < playMap::MAP_NUM; playMap_i++)
	{
		for (int bg_i = 0; bg_i < BG_NUM[playMap_i]; bg_i++)
		{
			m_bgHndl[playMap_i][bg_i] = -1;
		}
	}
	m_bgId = -1;
	m_bg.Init(INIT_POS);
}

//---------------------------
//		  画像ロード
//---------------------------
void CMapSelectBG::Load()
{
	for (int playMap_i = 0; playMap_i < playMap::MAP_NUM; playMap_i++)
	{
		for (int bg_i = 0; bg_i < BG_NUM[playMap_i]; bg_i++)
		{
			m_bgHndl[playMap_i][bg_i] = LoadGraph(BG_GRAPHIC_PATH[playMap_i][bg_i]);
		}
	}

	m_bg.SetHndl(m_bgHndl[0][0]);
}

//---------------------------
//	  毎フレームする処理
//---------------------------
void CMapSelectBG::Step()
{
}

//---------------------------
//		   画像描写
//---------------------------
void CMapSelectBG::Draw()
{
	m_bg.Draw();
}

//---------------------------
//		   終了処理
//---------------------------
void CMapSelectBG::Exit()
{
	for (int playMap_i = 0; playMap_i < playMap::MAP_NUM; playMap_i++)
	{
		for (int bg_i = 0; bg_i < BG_NUM[playMap_i]; bg_i++)
		{
			if (m_bgHndl[playMap_i][bg_i] != -1)
			{
				DeleteGraph(m_bgHndl[playMap_i][bg_i]);
				m_bgHndl[playMap_i][bg_i] = -1;
			}
		}
	}

}

