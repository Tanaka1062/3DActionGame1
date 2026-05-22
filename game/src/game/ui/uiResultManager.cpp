#include "uiResultManager.h"
#include "../data.h"
#include "../player/playerData.h"
#include "../ranking/ranking.h"
#include "../map/resultMap/resultMap.h"
#include <algorithm>
#include "../../lib/input/keyInput.h"

using namespace std;

enum tagUiName
{
	UI_WIN_PLAYER_TEXT,		//勝利したプレイヤーテキスト
	UI_RESULT_TEXT_1,		//リザルトテキスト1
	UI_RESULT_TEXT_2,		//リザルトテキスト2

	UI_NUM,					//UIの数
};

static const char* UI_WIN_PLAYER_GRAPHIC_PATH[PLAYER_NUM] =	//勝利したプレイヤーテキストの画像パス
{
	"data/graphic/result/resultTextPlayer1.png",
	"data/graphic/result/resultTextPlayer2.png",
	"data/graphic/result/resultTextPlayer3.png",
	"data/graphic/result/resultTextPlayer4.png",
};

static const char* UI_GRAPHIC_PATH[UI_NUM] =				//UIの画像パス
{
	"",
	"data/graphic/result/resultText1.png",
	"data/graphic/result/resultText2.png",
};

constexpr VECTOR UI_POS[UI_NUM] =							//UIの座標
{
	{WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y,0.0f},
	{WINDOW_SIZE_HALF_X,540.0f,0.0f},
	{WINDOW_SIZE_HALF_X,540.0f,0.0f},
};


//コンストラクタ・デストラクタ
CUiResultManager::CUiResultManager()
{
	for (int ui_i = 0; ui_i < UI_NUM; ui_i++)
	{
		C2DObject* ui = new C2DObject;

		m_ui.push_back(ui);
	}

	Init();
}

CUiResultManager::~CUiResultManager()
{
	Exit();

	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		delete m_ui[ui_i];
	}

	//全て消す
	m_ui.clear();
}

void CUiResultManager::Init()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Init(UI_POS[ui_i]);
		m_ui[ui_i]->SetActive(false);
	}

	m_lineGraph.Init();

	m_state = CUiResultManager::RANKING;
}

//ロード
void CUiResultManager::Load()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		if (ui_i == UI_WIN_PLAYER_TEXT)
		{
			CRanking* ranking = CRanking::GetInstance();

			m_ui[ui_i]->Load(UI_WIN_PLAYER_GRAPHIC_PATH[ranking->GetWinnerPlayerName()]);
		}
		else
		{
			m_ui[ui_i]->Load(UI_GRAPHIC_PATH[ui_i]);
		}
	}

	m_lineGraph.Load();
}

//毎フレームする処理
void CUiResultManager::Step(bool _isPodiumMoveEnd)
{
	switch (m_state)
	{
	case CUiResultManager::RANKING:
		if (_isPodiumMoveEnd == true)
		{
			for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
			{
				m_ui[ui_i]->SetActive(true);
			}

			//ボタンを押したらシーンをグラフに変更
			if(CKeyInput::IsTrg(KEY_SELECT) == true ||
				CControllerManager::IsTrg(BUTTON_B) == true)
			{
				m_state = CUiResultManager::GRAPH;
			}
		}
		break;
	case CUiResultManager::GRAPH:
		m_lineGraph.Step();
		if (m_lineGraph.GetIsMaxLine() == true)
		{
			//ボタンを押したらグラフを終了する
			if (CKeyInput::IsTrg(KEY_SELECT) == true ||
				CControllerManager::IsTrg(BUTTON_B) == true)
			{
				m_isGraphEnd = true;
			}
		}
		break;
	}

}

//描写
void CUiResultManager::Draw()
{
	m_ui[UI_WIN_PLAYER_TEXT]->Draw();

	switch (m_state)
	{
	case CUiResultManager::RANKING:
		m_ui[UI_RESULT_TEXT_1]->Draw();
		break;
	case CUiResultManager::GRAPH:
		m_lineGraph.Draw();

		//最後まで線が到達したらテキスト2を表示する
		if (m_lineGraph.GetIsMaxLine() == true)
		{
			m_ui[UI_RESULT_TEXT_2]->Draw();
		}
		break;
	}

}

//破棄
void CUiResultManager::Exit()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Exit();
	}

	m_lineGraph.Exit();
}

