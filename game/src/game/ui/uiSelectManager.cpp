#include "uiSelectManager.h"
#include "hpber/hpbar.h"
#include "../data.h"
#include "../gameTime/gameTime.h"
#include "../../lib/input/controllerManager.h"

using namespace std;

enum tagUiName
{
	UI_TEXT,		//テキスト
	UI_TEXT2,		//テキスト２

	UI_NUM,				//UIの数
};

static const char* UI_GRAPHIC_PATH[UI_NUM] =		//背景の画像パス
{
	"data/graphic/select/selectText.png",
	"data/graphic/select/selectText2.png",

};

static const VECTOR UI_POS[UI_NUM] =					//UIの座標
{
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),static_cast<float>(WINDOW_SIZE_Y * 0.5f) + 100.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),static_cast<float>(WINDOW_SIZE_Y * 0.5f) + 300.0f,0.0f},
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
void CUiSelectManager::Load()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->LoadGraphic(UI_GRAPHIC_PATH[ui_i]);
	}
}

//毎フレームする処理
void CUiSelectManager::Step()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Step();
	}

	for (int pad_i = 0; pad_i < PAD_NUM; pad_i++)
	{
		if (CControllerManager::IsConnection(static_cast<tagPadName>(pad_i)) == true)
		{
			switch (pad_i)
			{
			case PAD_1:

				break;
			case PAD_2:
				break;
			case PAD_3:
				break;
			case PAD_4:
				break;
			}
		}
	}
}

//描写
void CUiSelectManager::Draw()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Draw();
	}
}

//破棄
void CUiSelectManager::Exit()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Exit();
	}

	//終わるときに全て消す
	m_ui.clear();
}

