#include "uiMapSelectManager.h"
#include "../data.h"
#include "../gameTime/gameTime.h"
#include "../../lib/input/controllerManager.h"

using namespace std;


//コンストラクタ・デストラクタ
CUiMapSelectManager::CUiMapSelectManager()
{
	Init();
}

CUiMapSelectManager::~CUiMapSelectManager()
{
	Exit();
}

void CUiMapSelectManager::Init()
{
	m_mapSelect.Init();
}

//ロード
void CUiMapSelectManager::Load()
{
	m_mapSelect.Load();
}

//毎フレームする処理
void CUiMapSelectManager::Step()
{
	m_mapSelect.Step();
}

//描写
void CUiMapSelectManager::Draw()
{
	m_mapSelect.Drow();
}

//破棄
void CUiMapSelectManager::Exit()
{
	m_mapSelect.Exit();
}

