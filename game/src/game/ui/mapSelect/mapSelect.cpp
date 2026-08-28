#include "mapSelect.h"
#include "../../data.h"
#include "../../lib/input/controllerManager.h"

namespace {

	//マップ関連定義------------------------------------------------------------------
	constexpr const char*	STAGE_GRAPHIC_PATH[playMap::MAP_NUM] =		//マップの画像パス
	{
		"data/graphic/mapSelect/grassland/stage1.png",
		"data/graphic/mapSelect/grassland/stage1.png",
	};
	constexpr VECTOR		MAP_INIT_POS = 
	{ WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y,0.0f };						//マップの初期座標
	constexpr float			MAP_SPACING = 200.0f + WINDOW_SIZE_X;		//マップ同士の距離
	constexpr float			MAP_SCALE_MIN = 0.3f;						//マップの最小の大きさ
	constexpr float			MAP_SCALE_MAX = 0.5f;						//マップの最大の大きさ
	constexpr float			MAP_SCALE_CHANGE_SPEED = 0.03f;				//マップの大きさが変わる速さ
	constexpr float			MAP_SCALE_STOP_DISTANCE = 0.05f;			//マップの大きさの停止距離				
	constexpr float			MAP_MOVE_SPEED = 30.0f;						//マップの移動スピード
	constexpr float			MAP_STOP_DISTANCE = 10.0f;					//マップ停止距離
	//--------------------------------------------------------------------------------

	//フレーム関連定義----------------------------------------------------------------
	constexpr const char*	FRAME_GRAPHIC_PATH =						//フレームの画像パス
	{ "data/graphic/mapSelect/frame.png" };
	constexpr int			FRAME_SIZE_X = 960;							//フレームの画像サイズ横
	constexpr int			FRAME_SIZE_Y = 540;							//フレームの画像サイズ縦
	constexpr int			FRAME_ANIM_NUM = 4;							//フレームのアニメーションの数
	constexpr int			FRAME_ANIM_SPEED = 20;						//フレームのアニメーション再生速度
	constexpr float			FRAME_SCALE_RATIO = 2.0f;					//フレームの大きさの倍率
	//--------------------------------------------------------------------------------

	constexpr float			STICK_DEAD_ZONE = 0.3f;						//スティックのデットゾーン

	//矢印関連定義--------------------------------------------------------------------
	constexpr const char*	ARROW_GRAPHIC_PATH[CMapSelect::ARROW_NUM] =	//矢印の画像パス
	{
		"data/graphic/mapSelect/L_Arrow.png",
		"data/graphic/mapSelect/R_Arrow.png",
	};
	constexpr int			ARROW_SIZE = 128;							//矢印の画像サイズ
	constexpr int			ARROW_ANIM_NUM = 4;							//矢印のアニメーションの数
	constexpr int			ARROW_ANIM_SPEED = 20;						//矢印のアニメーション再生速度
	constexpr VECTOR		ARROW_INIT_POS[CMapSelect::ARROW_NUM]	=	//矢印の初期座標
	{
		{120.0f,WINDOW_SIZE_HALF_Y,0.0f},
		{WINDOW_SIZE_X - 120.0f,WINDOW_SIZE_HALF_Y,0.0f},
	};
	//--------------------------------------------------------------------------------

	//テキスト関連定義----------------------------------------------------------------
	constexpr const char*	TEXT_GRAPHIC_PATH =							//テキストの画像パス
	{
		"data/graphic/mapSelect/mapSelectText.png",
	};
	constexpr VECTOR		TEXT_INIT_POS =								//テキストの初期座標
	{ WINDOW_SIZE_HALF_X,WINDOW_SIZE_Y - 50.0f,0.0f };	
	//--------------------------------------------------------------------------------

	//マップテキスト関連定義----------------------------------------------------------
	constexpr const char*	MAP_TEXT_GRAPHIC_PATH[playMap::MAP_NUM] =	//マップテキストの画像パス
	{
		"data/graphic/mapSelect/grassland/mapText.png",
		"data/graphic/mapSelect/grassland/mapText.png",
	};
	constexpr VECTOR		MAP_TEXT_INIT_POS =							//マップテキストの初期座標
	{ WINDOW_SIZE_HALF_X,80.0f,0.0f };
	constexpr float			MAP_TEXT_SCALE_MAX = 1.0f;					//マップテキストの最大の大きさ
	constexpr float			MAP_TEXT_SCALE_CHANGE_SPEED = 0.06f;		//マップテキストの大きさが変わる速さ
	//--------------------------------------------------------------------------------
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
		VECTOR pos = MAP_INIT_POS;
		pos.x += MAP_SPACING * map_i;
		m_map[map_i].Init(pos);
		m_frame[map_i].Init(pos);

		if (map_i == playMap::MAP_1)
		{
			m_mapScale[map_i] = MAP_SCALE_MAX;
		}
		else
		{
			m_mapScale[map_i] = MAP_SCALE_MIN;
		}
		m_mapText[map_i].Init(MAP_TEXT_INIT_POS);
	}
	m_nowMap = static_cast<int>(playMap::MAP_1);
	m_isMove = false;

	for (int arrow_i = 0; arrow_i < CMapSelect::ARROW_NUM; arrow_i++)
	{
		m_arrow[arrow_i].Init(ARROW_INIT_POS[arrow_i]);
	}
	m_text.Init(TEXT_INIT_POS);
	m_mapTextScale = MAP_TEXT_SCALE_MAX;
	m_isMapSelect = false;
}

//画像ロード
void CMapSelect::Load()
{
	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		m_map[map_i].Load(STAGE_GRAPHIC_PATH[map_i]);
		m_frame[map_i].Load(FRAME_GRAPHIC_PATH,FRAME_ANIM_NUM, FRAME_SIZE_X, FRAME_SIZE_Y);
		m_frame[map_i].RequestAnim(0,FRAME_ANIM_SPEED);
		m_mapText[map_i].Load(MAP_TEXT_GRAPHIC_PATH[map_i]);
	}

	for (int arrow_i = 0; arrow_i < CMapSelect::ARROW_NUM; arrow_i++)
	{
		m_arrow[arrow_i].Load(ARROW_GRAPHIC_PATH[arrow_i],ARROW_ANIM_NUM,ARROW_SIZE,ARROW_SIZE);
		m_arrow[arrow_i].RequestAnim(0,ARROW_ANIM_SPEED);
	}

	m_text.Load(TEXT_GRAPHIC_PATH);
}

//毎フレームする処理
void CMapSelect::Step()
{
	//マップの切り替え処理-------------------------------------------------
	if (m_isMove == false)
	{
		CPlayMapData* mapData = CPlayMapData::GetInstance();
		//マップID設定
		mapData->SetSelectMap(static_cast<playMap::tagMapSelect>(m_nowMap));
		//一番右のマップが選択されていない場合矢印を表示
		if (m_nowMap < playMap::MAP_NUM - 1)
		{
			m_arrow[CMapSelect::RIGHT].SetActive(true);
			//入力があると次のマップに移動する
			if (CControllerManager::GetLX() > STICK_DEAD_ZONE)
			{
				m_nowMap++;
			}
		}
		else
		{
			m_arrow[CMapSelect::RIGHT].SetActive(false);
		}
		//一番左のマップが表示されていない場合
		if (m_nowMap > playMap::MAP_1)
		{
			m_arrow[CMapSelect::LEFT].SetActive(true);
			//入力があると前のマップに移動する
			if (CControllerManager::GetLX() < -STICK_DEAD_ZONE)
			{
				m_nowMap--;
			}
		}
		else
		{
			m_arrow[CMapSelect::LEFT].SetActive(false);
		}
		m_text.SetActive(true);

		//マップテキストを徐々に大きくする
		if (m_mapTextScale < MAP_TEXT_SCALE_MAX)
		{
			m_mapTextScale += MAP_TEXT_SCALE_CHANGE_SPEED;
		}

		//マップの決定
		if (CControllerManager::IsTrg(BUTTON_B))
		{
			m_isMapSelect = true;
		}
	}
	else
	{
		m_mapTextScale = 0.0f;
		m_text.SetActive(false);
	}
	//---------------------------------------------------------------------

	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		//マップ移動処理-------------------------------------------------------
		float posX = MAP_INIT_POS.x + MAP_SPACING * map_i;
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
		m_frame[map_i].SetPos(mapPos);
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
		
		//フレームのアニメーション
		m_frame[map_i].Step();
	}

	//矢印のアニメーション
	for (int arrow_i = 0; arrow_i < ARROW_NUM; arrow_i++)
	{
		m_arrow[arrow_i].Step();
	}
}

//描写処理
void CMapSelect::Drow()
{
	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		m_map[map_i].Draw(m_mapScale[map_i]);
		m_frame[map_i].Draw(m_mapScale[map_i] * FRAME_SCALE_RATIO);
	}
	
	m_mapText[m_nowMap].Draw(m_mapTextScale);

	for (int arrow_i = 0; arrow_i < CMapSelect::ARROW_NUM; arrow_i++)
	{
		m_arrow[arrow_i].Draw();
	}

	m_text.Draw();
}

//終了処理
void CMapSelect::Exit()
{
	for (int map_i = 0; map_i < playMap::MAP_NUM; map_i++)
	{
		m_map[map_i].Exit();
		m_frame[map_i].Exit();
		m_mapText[map_i].Exit();
	}

	for (int arrow_i = 0; arrow_i < CMapSelect::ARROW_NUM; arrow_i++)
	{
		m_arrow[arrow_i].Exit();
	}

	m_text.Exit();
}

