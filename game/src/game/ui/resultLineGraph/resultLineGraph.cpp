#include "resultLineGraph.h"
#include <DxLib.h>
#include "../../data.h"
#include <algorithm>
#include "../../ranking/ranking.h"

using namespace std;

constexpr VECTOR START_LINE = { 78.0f,609.0f,0.0f };						//はじめの線の座標
constexpr float LINE_LENGTH = WINDOW_SIZE_X - 288.0f;						//線の長さ
constexpr int LINE_SPEED = 3;												//線の伸びるスピード
constexpr int LINE_LENGTH_Y_MAX = 12;										//縦の線の最大の長さ
constexpr int LINE_LENGTH_Y = 10;											//線の縦の長さ

//UIのグラフィックパス
constexpr const char* GRAPHIC_UI_PATH =
{
	"data/graphic/result/lineGraph.png",
};

constexpr int UI_ALPHA = 200;						//UIの透明度
constexpr VECTOR UI_INIT_POS =						//UIの初期座標
{ WINDOW_SIZE_HALF_X,WINDOW_SIZE_HALF_Y,0.0f };	

constexpr VECTOR PANEL_INIT_POS =					//パネルの初期座標
{ UI_INIT_POS.x + 465.0f,200.0f,0.0f };

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
	m_lineLen = static_cast<int>(START_LINE.x);

	m_ui.Init(UI_INIT_POS);
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_playerPanel[player_i].Init();
	}

	m_isMaxLine = false;
}

//ロード
void CResultLineGraph::Load()
{
	m_ui.Load(GRAPHIC_UI_PATH);

	//プレイヤーの順位を取得する
	CRanking* ranking = CRanking::GetInstance();
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		tagPlayerName name = static_cast<tagPlayerName>(player_i);
		VECTOR pos = PANEL_INIT_POS;
		pos.y += 100.0f * ranking->GetPlayerRank(name);
		int money = ranking->GetPlayerGetCoin(name);
		m_playerPanel[player_i].Load(name, pos, money);
	}
}

//毎フレームする処理
void CResultLineGraph::Step()
{
	if (LINE_LENGTH <= m_lineLen)
		m_isMaxLine = true;

	if (m_isMaxLine == false)
	{
		//伸ばす
		m_lineLen += LINE_SPEED;
	}
}

//描写処理
void CResultLineGraph::Draw()
{
	//画像の透明度を変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, UI_ALPHA);
	m_ui.Draw();
	//画像の透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//プレイヤーの順位を取得する
	CRanking* ranking = CRanking::GetInstance();
	//一つの線の長さを求める
	int len = static_cast<int>((LINE_LENGTH - START_LINE.x)) / ranking->GetPlayerDataNum();
	//初めの線縦(保存用)
	int startLineY[PLAYER_NUM];
	fill(startLineY, startLineY + PLAYER_NUM, static_cast<int>(START_LINE.y));
	
	//線の描写-------------------------------------------------------------------------
	for (int data_i = 0; data_i < ranking->GetPlayerDataNum(); data_i++)
	{
		//初めの線横を求める
		int startLineX = static_cast<int>(START_LINE.x) + data_i * len;
		//横の終点を求める
		int endLineX = static_cast<int>(START_LINE.x) + (len * (data_i + 1));
		//現在の線が上で求めた線の中にいたら途中まで伸ばす
		if (startLineX <= m_lineLen && m_lineLen <= endLineX)
		{
			for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
			{
				//縦の終点を求める
				int endLineY = static_cast<int>(START_LINE.y) - (LINE_LENGTH_Y * ranking->GetPlayerData(data_i, player_i).m_coinNum);
				//現在の線が全体のどれくらい進んでいるかの割合を求める
				float lenY = static_cast<float>((m_lineLen - startLineX)) / static_cast<float>((endLineX - startLineX));
				//割合から今の縦の線の終点がどこにあるか求める
				lenY = (endLineY - startLineY[player_i]) * lenY + startLineY[player_i];
				//線の描写
				DrawLine(startLineX, startLineY[player_i] + player_i, m_lineLen, static_cast<int>(lenY) + player_i, PLAYER_COLOR[player_i], 5);
				//現在の縦の最終点を初めの線に保存する
				startLineY[player_i] = static_cast<int>(lenY);
			}
		}
		//現在の線が上で求めた線をすでに越していたら線を描写する
		else if (startLineX <= m_lineLen && endLineX <= m_lineLen)
		{
			for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
			{
				//縦の終点を求める
				int endLineY = static_cast<int>(START_LINE.y) - (LINE_LENGTH_Y * ranking->GetPlayerData(data_i, player_i).m_coinNum);
				//線の描写
				DrawLine(startLineX, startLineY[player_i] + player_i, endLineX, endLineY + player_i, PLAYER_COLOR[player_i], 5);
				//現在の縦の最終点を初めの線に保存する
				startLineY[player_i] = endLineY;
			}
		}
	}
	//---------------------------------------------------------------------------------

	//プレイヤーのパネルを表示
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_playerPanel[player_i].Draw();
	}
}

//終了処理
void CResultLineGraph::Exit()
{
	m_ui.Exit();
	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_playerPanel[player_i].Exit();
	}
}

