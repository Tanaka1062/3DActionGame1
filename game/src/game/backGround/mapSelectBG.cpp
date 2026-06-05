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
	constexpr int ALPHA_MAX = 200;					//最大の透明度
	constexpr int ALPHA_MIN = 60;					//最小の透明度
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
	m_bgId = 0;
	m_mapId = static_cast<int>(playMap::MAP_1);
	m_bg.Init(INIT_POS);
	m_alpha = ALPHA_MAX;
	m_isFadeOutEnd = false;
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
	CPlayMapData* playMapData = CPlayMapData::GetInstance();
	//マップが切り替わると背景を変更する
	if (m_mapId != playMapData->GetSelectMap())
	{
		m_mapId = playMapData->GetSelectMap();
		m_bgId = 0;
		m_alpha = ALPHA_MAX;
	}

	if (m_isFadeOutEnd == false)
	{
		//背景を徐々に透明にする
		m_alpha--;
		//完全に透明になったら背景を変更する
		if (m_alpha <= ALPHA_MIN)
		{
			m_bgId++;
			//背景の数を超えたら初期値に戻す
			if (m_bgId >= BG_NUM[m_mapId])
			{
				m_bgId = 0;
			}
			m_isFadeOutEnd = true;
		}

	}
	else
	{
		//背景を徐々に表示する
		m_alpha++;
		//最大の透明度を超えたら透明になるように戻す
		if (m_alpha >= ALPHA_MAX)
		{
			m_isFadeOutEnd = false;
		}
	}

	//背景画像更新
	m_bg.SetHndl(m_bgHndl[m_mapId][m_bgId]);
}

//---------------------------
//		   画像描写
//---------------------------
void CMapSelectBG::Draw()
{
	//画像の透明度を変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	m_bg.Draw();
	//画像の透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

