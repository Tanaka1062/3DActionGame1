#include "mapSelect.h"
#include "../../data.h"
#include "../../lib/input/controllerManager.h"

namespace {
	static const char* STAGE_GRAPHIC_PATH[CMapSelect::MAP_NUM] =	//マップの画像パス
	{
		"data/graphic/mapSelect/grassland/stage1.png",
		"data/graphic/mapSelect/grassland/stage1.png",
	};

	constexpr VECTOR INIT_POS = 
	{ WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y,0.0f };					//マップの初期座標
	constexpr float MAP_SPACING = 200.0f + WINDOW_SIZE_X;			//マップ同士の距離
	constexpr float MAP_SCALE = 0.5f;								//マップの大きさ
	constexpr float MAP_MOVE_SPEED = 6.0f;							//マップの移動スピード

	constexpr float STICK_DEAD_ZONE = 0.3f;							//スティックのデットゾーン
}

//コンストラクタ
CMapSelect::CMapSelect()
{
	Init();
}
//デストラクタ
CMapSelect::~CMapSelect()
{
	Exit();
}

//初期化
void CMapSelect::Init()
{
	for (int map_i = 0; map_i < CMapSelect::MAP_NUM; map_i++)
	{
		VECTOR pos = INIT_POS;
		pos.x += MAP_SPACING * map_i;
		m_map[map_i].Init(pos);
	}
	m_nowMap = MAP_1;
}

//画像ロード
void CMapSelect::Load()
{
	for (int map_i = 0; map_i < CMapSelect::MAP_NUM; map_i++)
	{
		m_map[map_i].Load(STAGE_GRAPHIC_PATH[map_i]);
	}
}

//毎フレームする処理
void CMapSelect::Step()
{
	if (CControllerManager::GetLX() > STICK_DEAD_ZONE &&
		m_nowMap < MAP_NUM)
	{
		m_nowMap++;
	}
	else if (CControllerManager::GetLX() < -STICK_DEAD_ZONE &&
		m_nowMap > MAP_1)
	{
		m_nowMap--;
	}

	for (int map_i = 0; map_i < CMapSelect::MAP_NUM; map_i++)
	{
		float posX = INIT_POS.x + MAP_SPACING * map_i;
		posX -= m_nowMap * MAP_SPACING;
		VECTOR mapPos = m_map[map_i].GetPos();
		if (posX > mapPos.x)
		{
			mapPos.x += MAP_MOVE_SPEED;
		}
		else if (posX < mapPos.x)
		{
			mapPos.y -= MAP_MOVE_SPEED;
		}
		m_map->SetPos(mapPos);
	}
}

//描写処理
void CMapSelect::Drow()
{
	for (int map_i = 0; map_i < CMapSelect::MAP_NUM; map_i++)
	{
		m_map[map_i].Draw(MAP_SCALE);
	}
}

//終了処理
void CMapSelect::Exit()
{
	for (int map_i = 0; map_i < CMapSelect::MAP_NUM; map_i++)
	{
		m_map[map_i].Exit();
	}
}

