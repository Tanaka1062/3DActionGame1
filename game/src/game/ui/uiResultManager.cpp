#include "uiResultManager.h"
#include "../data.h"
#include "../player/playerData.h"
#include "../ranking/ranking.h"
#include "../map/resultMap/resultMap.h"
#include <algorithm>

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
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),static_cast<float>(WINDOW_SIZE_Y * 0.5f),0.0f},
	{static_cast<float>(WINDOW_SIZE_X * 0.5f),540.0f,0.0f},

};

constexpr VECTOR START_LINE = { 120.0f,700.0f,0.0f };
constexpr float LINE_LENGTH = static_cast<float>(WINDOW_SIZE_X - 120.0f);


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
void CUiResultManager::Step(CMapBase* _map)
{
	if (_map->GetMapId() == MAP_ID_RESULT)
	{
		CResultMap* resultMap = dynamic_cast<CResultMap*>(_map);
		if (resultMap->GetIsPodiumMoveEnd() == true)
		{
			for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
			{
				m_ui[ui_i]->SetActive(true);
			}
		}
	}

	m_lineGraph.Step();
}

//描写
void CUiResultManager::Draw()
{
	for (int ui_i = 0; ui_i < m_ui.size(); ui_i++)
	{
		m_ui[ui_i]->Draw();
	}

	m_lineGraph.Draw();

	//int x = 64;
	//int y = 64;
	//CRanking* ranking = CRanking::GetInstance();
	//for (int i = 0; i < ranking->GetPlayerDataNum(); i++)
	//{
	//	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	//	{
	//		DrawFormatString(x + (140 * i), y + (32 * player_i), GetColor(255, 0, 0), "プレイヤー%d = %d",
	//			player_i, ranking->GetPlayerData(i, player_i).m_coinNum);
	//	}
	//}
	//int startX = 120;
	//int startY = 700;
	//int endX = WINDOW_SIZE_X - 120;
	//int len = endX - startX;
	//int len2 = len / ranking->GetPlayerDataNum();

	//int lineX[PLAYER_NUM];
	//fill(lineX, lineX + PLAYER_NUM, startX);
	//int lineY[PLAYER_NUM];
	//fill(lineY, lineY + PLAYER_NUM, startY);
	//for (int i = 0; i < ranking->GetPlayerDataNum(); i++)
	//{
	//	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	//	{
	//		int lineX2 = startX + (len2 * (i + 1));
	//		int lineY2 = startY - (10 * ranking->GetPlayerData(i, player_i).m_coinNum);
	//		DrawLine(lineX[player_i], lineY[player_i] + player_i, lineX2, lineY2 + player_i, PLAYER_COLOR[player_i],5);
	//		lineX[player_i] = lineX2;
	//		lineY[player_i] = lineY2;
	//	}
	//}

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

