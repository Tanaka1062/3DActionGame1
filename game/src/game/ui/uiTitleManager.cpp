#include "uiTitleManager.h"
#include "hpber/hpbar.h"
#include "../data.h"
#include "../gameTime/gameTime.h"

enum tagUiName
{
	UI_BACKGROUND,		//背景
	UI_TITLE,			//タイトル

	UI_NUM,				//UIの数
};

constexpr const char* UI_GRAPHIC_PATH[UI_NUM] =		//背景の画像パス
{
	"data/graphic/title/backGround.png",
	"data/graphic/title/title.png",

};

static const VECTOR UI_POS[UI_NUM] =					//UIの座標
{
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),static_cast<float>(WINDOW_SIZE_Y * 0.5f),0.0f},
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),200.0f,0.0f},
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
	//一旦すべて削除
	m_ui.clear();

	for (int ui_i = 0; ui_i < UI_NUM; ui_i++)
	{
		C2DUi* ui = new C2DUi;

		ui->Init(UI_POS[ui_i]);

		m_ui.push_back(ui);
	}
}

//ロード
void CUiTitleManager::Load()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->LoadGraphic(UI_GRAPHIC_PATH[ui_i]);
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

	//終わるときに全て消す
	m_ui.clear();
}

