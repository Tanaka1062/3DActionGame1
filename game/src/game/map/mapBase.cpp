#include "mapBase.h"
#include <math.h>
#include "../gameTime/gameTime.h"

using namespace std;

//定義関連==================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };	//大きさ
constexpr int MAP_MOVE_TIME = 30;				//ステージが移動するまでの時間

//==========================================


//------------------------
//	コンストラクタ
//------------------------
CMapBase::CMapBase()
{
	Init();
}

//------------------------
//	デストラクタ
//------------------------
CMapBase::~CMapBase()
{
	Exit();

	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		delete m_stage[stage_i];
	}
	m_stage.clear();

	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		delete m_object[object_i];
	}
	m_object.clear();
}

//------------------------
//		初期化
//------------------------
void CMapBase::Init(int _mapId)
{
	m_mapId = _mapId;
	m_stageId = 0;
	m_mapMoveTimer = 0;

	tagStageSpawnData initData;
	memset(&initData, 0, sizeof(initData));
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stageSpawnData.push_back(initData);
	}
}

//------------------------
//		モデルロード
//------------------------
void CMapBase::Load()
{
}

//------------------------
//	毎フレームする処理
//------------------------
void CMapBase::Step()
{

}

//------------------------
//		　更新処理
//------------------------
void CMapBase::Update()
{
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stage[stage_i]->Update();
	}

	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		m_object[object_i]->Update();
	}
}

//------------------------
//		モデル描写
//------------------------
void CMapBase::Draw()
{
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		if (m_stage[stage_i]->GetActive() == false)continue;

		m_stage[stage_i]->Draw();
	}

	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		if (m_object[object_i]->GetActive() == false)continue;

		m_object[object_i]->Draw();
	}
}

//------------------------
//		終了処理
//------------------------
void CMapBase::Exit()
{
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stage[stage_i]->Exit();
	}

	m_stageSpawnData.clear();

	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		m_object[object_i]->Exit();
	}
}

