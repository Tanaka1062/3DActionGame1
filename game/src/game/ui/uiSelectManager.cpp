#include "uiSelectManager.h"
#include "../data.h"
#include "../gameTime/gameTime.h"
#include "../../lib/input/controllerManager.h"

using namespace std;

constexpr const char* UI_GRAPHIC_PATH[UiSelectData::UI_NUM] =		//背景の画像パス
{
	"data/graphic/select/selectText.png",
	"data/graphic/select/selectText2.png",

};

static const VECTOR UI_POS[UiSelectData::UI_NUM] =					//UIの座標
{
	{WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y + 100.0f,0.0f},
	{WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y + 300.0f,0.0f},
};

//コンストラクタ・デストラクタ
CUiSelectManager::CUiSelectManager()
{
	Init();
}

CUiSelectManager::~CUiSelectManager()
{
	Exit();
}

void CUiSelectManager::Init()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Init();
	}

	m_countDown.Init();
}

//ロード
void CUiSelectManager::Load()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Load(UI_GRAPHIC_PATH[ui_i]);
	}
	m_countDown.Load();
}

//毎フレームする処理
void CUiSelectManager::Step(bool _allReady)
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Step();
	}

	m_countDown.Step(_allReady);
}

//描写
void CUiSelectManager::Draw()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Draw();
	}
	m_countDown.Draw();
}

//破棄
void CUiSelectManager::Exit()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Exit();
	}
	m_countDown.Exit();
}

