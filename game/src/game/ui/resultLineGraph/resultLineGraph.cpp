#include "resultLineGraph.h"
#include <DxLib.h>
#include "../../data.h"
#include <algorithm>
#include "../../ranking/ranking.h"

using namespace std;

constexpr VECTOR START_LINE = { 120.0f,700.0f,0.0f };
constexpr float LINE_LENGTH = static_cast<float>(WINDOW_SIZE_X - 120.0f);
constexpr int LINE_SPEED = 2;

//UIのグラフィックパス
const char* GRAPHIC_UI_PATH =
{
	"data/graphic/result/lineGraph.png",
};

constexpr int UI_BLEND = 200;						//UIの透明度
constexpr VECTOR UI_INIT_POS =						//UIの初期座標
{ WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y,0.0f };	

//コンストラクタ
CResultLineGraph::CResultLineGraph()
{
	Init();
}

//デストラクタ
CResultLineGraph::~CResultLineGraph()
{
	Exit();
}

//初期化
void CResultLineGraph::Init()
{
	m_lineLen = START_LINE.x;

	m_ui.Init(UI_INIT_POS);
}

//ロード
void CResultLineGraph::Load()
{
	m_ui.Load(GRAPHIC_UI_PATH);
}

//毎フレームする処理
void CResultLineGraph::Step()
{
	//伸ばす
	m_lineLen += LINE_SPEED;
}

//描写処理
void CResultLineGraph::Draw()
{
	//画像の透明度を変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, UI_BLEND);
	m_ui.Draw();
	//画像の透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	CRanking* ranking = CRanking::GetInstance();

	int len = static_cast<int>((LINE_LENGTH - START_LINE.x)) / ranking->GetPlayerDataNum();

	int endLineY[PLAYER_NUM];
	fill(endLineY, endLineY + PLAYER_NUM, START_LINE.y);
	for (int data_i = 0; data_i < ranking->GetPlayerDataNum(); data_i++)
	{
		int startLineX = START_LINE.x + data_i * len;

		int lineX2 = START_LINE.x + (len * (data_i + 1));
		if (startLineX <= m_lineLen && m_lineLen <= lineX2)
		{
			for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
			{
				int lineY2 = START_LINE.y - (10 * ranking->GetPlayerData(data_i, player_i).m_coinNum);
				
				float lenY = static_cast<float>((m_lineLen - startLineX)) / static_cast<float>((lineX2 - startLineX));
				lenY = (lineY2 - endLineY[player_i]) * lenY + endLineY[player_i];

				DrawLine(startLineX, endLineY[player_i] + player_i, m_lineLen, static_cast<int>(lenY) + player_i, PLAYER_COLOR[player_i], 5);
				endLineY[player_i] = static_cast<int>(lenY);
			}
		}
		else if (startLineX <= m_lineLen && lineX2 <= m_lineLen)
		{
			for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
			{
				int lineY2 = START_LINE.y - (10 * ranking->GetPlayerData(data_i, player_i).m_coinNum);

				DrawLine(startLineX, endLineY[player_i] + player_i, lineX2, lineY2 + player_i, PLAYER_COLOR[player_i], 5);
				endLineY[player_i] = lineY2;
			}
		}
	}
}

//終了処理
void CResultLineGraph::Exit()
{
	m_ui.Draw();
}

