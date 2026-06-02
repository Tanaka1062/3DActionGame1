#include "mapSelect.h"
#include "../../data.h"
#include "../../lib/input/controllerManager.h"

namespace {
	static const char* STAGE_GRAPHIC_PATH[playMap::MAP_NUM] =	//マップの画像パス
	{
		"data/graphic/mapSelect/grassland/stage1.png",
		"data/graphic/mapSelect/grassland/stage1.png",
	};

	constexpr VECTOR INIT_POS = 
	{ WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y,0.0f };					//マップの初期座標
	constexpr float MAP_SPACING = 200.0f + WINDOW_SIZE_X;			//マップ同士の距離
	constexpr float MAP_SCALE_MIN = 0.3f;							//マップの最小の大きさ
	constexpr float MAP_SCALE_MAX = 0.5f;							//マップの最大の大きさ
	constexpr float MAP_SCALE_CHANGE_SPEED = 0.03f;					//マップの大きさが変わる速さ
	constexpr float MAP_SCALE_STOP_DISTANCE = 0.05f;				//マップの大きさの停止距離				
	constexpr float MAP_MOVE_SPEED = 30.0f;							//マップの移動スピード
	constexpr float MAP_STOP_DISTANCE = 10.0f;						//マップ停止距離

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
	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		VECTOR pos = INIT_POS;
		pos.x += MAP_SPACING * map_i;
		m_map[map_i].Init(pos);

		if (map_i == playMap::MAP_1)
		{
			m_mapScale[map_i] = MAP_SCALE_MAX;
		}
		else
		{
			m_mapScale[map_i] = MAP_SCALE_MIN;
		}
	}
	m_nowMap = static_cast<int>(playMap::MAP_1);
	m_isMove = false;
}

//画像ロード
void CMapSelect::Load()
{
	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		m_map[map_i].Load(STAGE_GRAPHIC_PATH[map_i]);
	}
}

//毎フレームする処理
void CMapSelect::Step()
{
	//マップの切り替え処理-------------------------------------------------
	if (m_isMove == false)
	{
		CPlayMapData* mapData = CPlayMapData::GetInstance();

		mapData->SetSelectMap(static_cast<playMap::tagMapSelect>(m_nowMap));

		if (CControllerManager::GetLX() > STICK_DEAD_ZONE &&
			m_nowMap < playMap::MAP_NUM - 1)
		{
			m_nowMap++;
		}
		else if (CControllerManager::GetLX() < -STICK_DEAD_ZONE &&
			m_nowMap > playMap::MAP_1)
		{
			m_nowMap--;
		}
	}
	//---------------------------------------------------------------------

	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		//マップ移動処理-------------------------------------------------------
		float posX = INIT_POS.x + MAP_SPACING * map_i;
		posX -= m_nowMap * MAP_SPACING;
		VECTOR mapPos = m_map[map_i].GetPos();
		if (abs(posX - mapPos.x) <= MAP_STOP_DISTANCE)
		{
			m_isMove = false;
			mapPos.x = posX;
		}
		else if (posX > mapPos.x)
		{
			m_isMove = true;
			mapPos.x += MAP_MOVE_SPEED;
		}
		else if (posX < mapPos.x)
		{
			m_isMove = true;
			mapPos.x -= MAP_MOVE_SPEED;
		}
		m_map[map_i].SetPos(mapPos);
		//---------------------------------------------------------------------

		//マップの大きさ変更処理-----------------------------------------------
		if (map_i == m_nowMap)
		{
			if (m_isMove == true)continue;

			if (abs(m_mapScale[map_i] - MAP_SCALE_MAX) == MAP_SCALE_STOP_DISTANCE)
			{
				m_mapScale[map_i] = MAP_SCALE_MAX;
			}
			else if (m_mapScale[map_i] < MAP_SCALE_MAX)
			{
				m_mapScale[map_i] += MAP_SCALE_CHANGE_SPEED;
			}
		}
		else
		{
			if (abs(m_mapScale[map_i] - MAP_SCALE_MIN) == MAP_SCALE_STOP_DISTANCE)
			{
				m_mapScale[map_i] = MAP_SCALE_MIN;
			}
			else if (m_mapScale[map_i] > MAP_SCALE_MIN)
			{
				m_mapScale[map_i] -= MAP_SCALE_CHANGE_SPEED;
			}
		}
		//---------------------------------------------------------------------
	}

}

//描写処理
void CMapSelect::Drow()
{
	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		m_map[map_i].Draw(m_mapScale[map_i]);
	}
}

//終了処理
void CMapSelect::Exit()
{
	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		m_map[map_i].Exit();
	}
}

