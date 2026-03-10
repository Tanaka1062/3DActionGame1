#include "grassland.h"
#include "../../../gameTime/gameTime.h"

//定義関連==================================
constexpr int STAGE_NUM = 5;					//ステージの数
constexpr VECTOR POS[STAGE_NUM] =
{
	{0.0f,0.0f,0.0f},
	{0.0f,0.0f,-600.0f },
	{0.0f,0.0f,-1200.0f},
	{0.0f,0.0f,-1800.0f},
	{0.0f,0.0f,-2400.0f},
};

constexpr VECTOR MOVE_SPEED = {0.0f,-10.0f,0.0f};	//動くスピード
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };			//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };		//大きさ
constexpr int SHAKE_AMOUNT = 2;						//揺れる大きさ
constexpr int SHAKE_TIME = 7;						//揺れるまでの時間
constexpr float FALL_MAX = -300.0f;					//最大の落下位置
static const char* MAP_MODEL_PATH[STAGE_NUM] ={
	"data/model/map/playMap/testMap10/TestMap10-1.mv1",
	"data/model/map/playMap/testMap10/TestMap10-2.mv1",
	"data/model/map/playMap/testMap10/TestMap10-3.mv1",
	"data/model/map/playMap/testMap10/TestMap10-4.mv1",
	"data/model/map/playMap/testMap10/TestMap10-5.mv1",

};					//ロードするファイル名
constexpr int MAP_MOVE_TIME = 30;			//ステージが移動するまでの時間

constexpr int MAPITEM_FRAME_NUM[STAGE_NUM] = {
	16,
	25,
	25,
	25,
	25,
};
constexpr int MAPITEM_SPAWN_NUM[STAGE_NUM] = {
	4,
	4,
	4,
	4,
	4,
};
constexpr int ITEM_FRAME_NUM[STAGE_NUM] = {
	0,
	16,
	16,
	16,
	16,
};
constexpr int ITEM_SPAWN_NUM[STAGE_NUM] = {
	0,
	4,
	4,
	4,
	4,
};
constexpr int COIN_FRAME_NUM[STAGE_NUM] = {
	25,
	34,
	34,
	34,
	34,
};
constexpr int COIN_SPAWN_NUM[STAGE_NUM] = {
	22,
	6,
	18,
	20,
	9,
};

//==========================================

//------------------------
//	コンストラクタ
//------------------------
CGrassland::CGrassland()
{
	for (int stage_i = 0; stage_i < STAGE_NUM; stage_i++)
	{
		m_stage.push_back(new CObject);
	}
	CMapBase::Init();
	Init();
}

//------------------------
//		初期化
//------------------------
void CGrassland::Init()
{
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stage[stage_i]->Init();
		m_stage[stage_i]->SetPos(POS[stage_i]);

		m_stageSpawnData[stage_i].coinFrameNum = COIN_FRAME_NUM[stage_i];
		m_stageSpawnData[stage_i].coinSpawnNum = COIN_SPAWN_NUM[stage_i];
		m_stageSpawnData[stage_i].itemFrameNum = ITEM_FRAME_NUM[stage_i];
		m_stageSpawnData[stage_i].itemSpawnNum = ITEM_SPAWN_NUM[stage_i];
		m_stageSpawnData[stage_i].mapItemFrameNum = MAPITEM_FRAME_NUM[stage_i];
		m_stageSpawnData[stage_i].mapItemSpawnNum = MAPITEM_SPAWN_NUM[stage_i];

	}

	m_stageId = 0;
	m_isStageFall = false;
	m_isStageShake = false;
}

//------------------------
//		モデルロード
//------------------------
void CGrassland::Load()
{
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stage[stage_i]->LoadModel(MAP_MODEL_PATH[stage_i]);

		CMapBase::Update();
		MV1RefreshCollInfo(m_stage[stage_i]->GetHndl());
	}
}

//------------------------
//	毎フレームする処理
//------------------------
void CGrassland::Step()
{
	StageMove();

	CGameTime* gameTime = CGameTime::GetInstance();

	//決められた時間だけ通る
	if (gameTime->GetTime() - m_mapMoveTimer == MAP_MOVE_TIME)
	{
		m_isStageFall = true;
		m_isStageShake = false;

		m_mapMoveTimer += MAP_MOVE_TIME;

		m_stageId += 1;

		if (m_stageId >= STAGE_NUM - 1)
		{
			m_stageId = STAGE_NUM - 1;
		}
	}
	else if (gameTime->GetTime() - m_mapMoveTimer >= MAP_MOVE_TIME - SHAKE_TIME)
	{
		StageShake();
		m_isStageShake = true;
	}
	int num = gameTime->GetTime() - m_mapMoveTimer;

	if (m_isStageFall == true)
	{
		StageMove();
	}

	if (m_isStageShake == true)
	{
		StageShake();
	}
}

//------------------------
//	ステージの移動処理
//------------------------
void CGrassland::StageMove()
{
	if (m_stageId - 1 >= 0)
	{
		VECTOR vec = m_stage[m_stageId - 1]->GetPos();
		m_stage[m_stageId - 1]->SetPos(VAdd(vec,MOVE_SPEED));

		if (m_stage[m_stageId - 1]->GetPos().y <= FALL_MAX)
		{
			m_isStageFall = false;
		}
	}
}

//------------------------
//	ステージの揺れる処理
//------------------------
void CGrassland::StageShake()
{
	if (m_stageId  >= 0)
	{
		VECTOR shake = { 0 };
		shake.x = GetRand(SHAKE_AMOUNT) - (SHAKE_AMOUNT * 0.5);
		shake.z = GetRand(SHAKE_AMOUNT) - (SHAKE_AMOUNT * 0.5);
		
		VECTOR vec = VAdd(POS[m_stageId],shake);
		m_stage[m_stageId]->SetPos(vec);
	}
}

