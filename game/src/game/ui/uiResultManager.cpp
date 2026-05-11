#include "uiResultManager.h"
#include "../data.h"
#include "../gameTime/gameTime.h"
#include "../player/playerData.h"

using namespace std;

enum tagUiName
{
	UI_WIN_PLAYER_TEXT,		//勝利したプレイヤーテキスト
	UI_RESULT_TEXT,			//リザルトテキスト

	UI_NUM,					//UIの数
};

static const char* UI_WIN_PLAYER_GRAPHIC_PATH[PLAYER_NUM] =	//勝利したプレイヤーテキストの画像パス
{
	"data/graphic/result/resultText1.png",
	"data/graphic/result/resultText2.png",
	"data/graphic/result/resultText3.png",
	"data/graphic/result/resultText4.png",
};

static const char* UI_GRAPHIC_PATH[UI_NUM] =				//UIの画像パス
{
	"",
	"data/graphic/result/resultText.png",

};

constexpr VECTOR UI_POS[UI_NUM] =							//UIの座標
{
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),180.0f,0.0f},
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),400.0f,0.0f},

};

//コンストラクタ・デストラクタ
CResultManager::CResultManager()
{
	Init();
}

CResultManager::~CResultManager()
{
	Exit();
}

void CResultManager::Init()
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
void CResultManager::Load()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Load(UI_GRAPHIC_PATH[ui_i]);
	}

}

//毎フレームする処理
void CResultManager::Step()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Step();
	}
}

//描写
void CResultManager::Draw()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Draw();
	}
}

//破棄
void CResultManager::Exit()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Exit();

		delete m_ui[ui_i];
	}

	//終わるときに全て消す
	m_ui.clear();
}

