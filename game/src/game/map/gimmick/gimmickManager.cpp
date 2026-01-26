#include "gimmickManager.h"
#include "moveBlock.h"
#include "../map.h"

using namespace std;

enum tagGimmickName
{
	GIMMICK_NAME_MOVE_BLOCK,		//動くブロックのギミック

	GIMMICK_NAME_NUM,				//ギミックの名前の数
};

static const char* MODEL_PATH[GIMMICK_NAME_NUM] =
{ "data/model/map/gimmick/gimmickMoveBlock.mv1" };			//ロードするファイル名

constexpr int MAP_FRAME_NUM[GIMMICK_NAME_NUM] = 
{
	79,
};


CGimmickManager::CGimmickManager()
{

}

CGimmickManager::~CGimmickManager()
{
	Exit();
}

//初期化
void CGimmickManager::Init()
{
	m_gimmick.push_back(new CMoveBlock);

	for (int gimmick_i = 0; gimmick_i < m_gimmick.size(); gimmick_i++)
	{
		m_gimmick[gimmick_i]->Init();
	}
}

//オブジェクトのロード
void CGimmickManager::Load()
{
	for (int gimmick_i = 0; gimmick_i < m_gimmick.size(); gimmick_i++)
	{
		m_gimmick[gimmick_i]->Load(MODEL_PATH[gimmick_i],MAP_FRAME_PATH[MAP_ID_GRASSLAND],MAP_FRAME_NUM[gimmick_i]);
	}
}

//毎フレームする処理
void CGimmickManager::Step()
{
	for (int gimmick_i = 0; gimmick_i < m_gimmick.size(); gimmick_i++)
	{
		m_gimmick[gimmick_i]->Step();
	}
}

//数値の更新
void CGimmickManager::Update()
{
	for (int gimmick_i = 0; gimmick_i < m_gimmick.size(); gimmick_i++)
	{
		m_gimmick[gimmick_i]->Update();
	}
}

//オブジェクトの描写
void CGimmickManager::Draw()
{
	for (int gimmick_i = 0; gimmick_i < m_gimmick.size(); gimmick_i++)
	{
		m_gimmick[gimmick_i]->Draw();
	}
}

//終了処理
void CGimmickManager::Exit()
{
	for (int gimmick_i = 0; gimmick_i < m_gimmick.size(); gimmick_i++)
	{
		m_gimmick[gimmick_i]->Exit();

		delete m_gimmick[gimmick_i];
	}
	m_gimmick.clear();
}

