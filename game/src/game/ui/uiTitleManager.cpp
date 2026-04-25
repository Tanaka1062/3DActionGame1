#include "uiTitleManager.h"
#include "../data.h"
#include "../gameTime/gameTime.h"

using namespace std;

enum tagUiName
{
	UI_TITLE,			//タイトル
	UI_START_TEXT,		//スタートテキスト

	UI_NUM,				//UIの数
};

static const char* UI_GRAPHIC_PATH[UI_NUM] =		//背景の画像パス
{
	"data/graphic/title/title.png",
	"data/graphic/title/startText.png",

};

constexpr VECTOR UI_POS[UI_NUM] =					//UIの座標
{
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),180.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),400.0f,0.0f},

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
	//増えすぎないように
	if (m_ui.size() == UI_NUM)return;

	for (int ui_i = 0; ui_i < UI_NUM; ui_i++)
	{
		C2DObject* ui = new C2DObject;

		ui->Init(UI_POS[ui_i]);

		m_ui.push_back(ui);
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

		delete m_ui[ui_i];
	}

	//終わるときに全て消す
	m_ui.clear();
}

