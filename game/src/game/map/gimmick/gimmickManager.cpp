#include "gimmickManager.h"

static const char* MODEL_PATH[] =
{ "data/model/map/gimmick/gimmickMoveBlock.mv1" };			//ロードするファイル名


CGimmickManager::CGimmickManager()
{
	Init();
}

CGimmickManager::~CGimmickManager()
{
	Exit();
}

//初期化
void CGimmickManager::Init()
{
	m_moveBlock.Init();
}

//オブジェクトのロード
void CGimmickManager::Load()
{
	m_moveBlock.Load(MODEL_PATH[0]);
}

//毎フレームする処理
void CGimmickManager::Step()
{
	m_moveBlock.Step();
}

//数値の更新
void CGimmickManager::Update()
{
	m_moveBlock.Update();
}

//オブジェクトの描写
void CGimmickManager::Draw()
{
	m_moveBlock.Draw();
}

//終了処理
void CGimmickManager::Exit()
{
	m_moveBlock.Exit();
}
