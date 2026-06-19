#include "uiTitleManager.h"
#include "../data.h"
#include "../gameTime/gameTime.h"

using namespace std;


constexpr const char* UI_GRAPHIC_PATH[UiTitleData::UI_NUM] =		//背景の画像パス
{
	"data/graphic/title/title.png",
	"data/graphic/title/startText.png",

};

constexpr VECTOR UI_POS[UiTitleData::UI_NUM] =					//UIの座標
{
	{WINDOW_SIZE_HALF_X,180.0f,0.0f},
	{WINDOW_SIZE_HALF_X,400.0f,0.0f},

};

//コンストラクタ・デストラクタ
CUiTitleManager::CUiTitleManager()
{
	Init();
}

CUiTitleManager::~CUiTitleManager()
{
	Exit();
}

void CUiTitleManager::Init()
{

	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Init(UI_POS[ui_i]);
	}
}

//ロード
void CUiTitleManager::Load()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Load(UI_GRAPHIC_PATH[ui_i]);
	}

}

//毎フレームする処理
void CUiTitleManager::Step()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Step();
	}
}

//描写
void CUiTitleManager::Draw()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Draw();
	}
}

//破棄
void CUiTitleManager::Exit()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Exit();
	}
}

