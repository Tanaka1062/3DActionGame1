#include "playerStatusPanel.h"

using namespace std;

//パネルの名前
enum tagPlayerStatusPanel
{
	PANEL_PLAYER1,							//プレイヤー1のパネル
	PANEL_PLAYER2,							//プレイヤー2のパネル
	PANEL_PLAYER3,							//プレイヤー3のパネル
	PANEL_PLAYER4,							//プレイヤー4のパネル

	PANEL_NUM,								//パネルの数
};

//ハートの状態
enum tagHeartState
{
	HEART_EMPTY,							//空
	HEART_QUARTER,							//4分の1
	HEART_HALF,								//半分
	HEART_THREE_QUARTER,					//4分の3
	HEART_FULL,								//満タン

	HEART_STATE_NUM,						//ハートの状態の数
};

//パネルのグラフィックパス
const char* GRAPHIC_PANEL_PATH[PANEL_NUM] =
{
	"data/graphic/ui/player1StatusPanel.png",
	"data/graphic/ui/player2StatusPanel.png",
	"data/graphic/ui/player3StatusPanel.png",
	"data/graphic/ui/player4StatusPanel.png",

};

//アイコンのグラフィックパス
const char* GRAPHIC_ICON_PATH[PANEL_NUM] =
{
	"data/graphic/ui/player1Icon.png",
	"data/graphic/ui/player2Icon.png",
	"data/graphic/ui/player3Icon.png",
	"data/graphic/ui/player4Icon.png",
};

//ハートのグラフィックパス
const char* GRAPHIC_HEART_PATH =
{
	"data/graphic/ui/heart.png",
};

constexpr int HEART_SIZE_X = 21;			//ハートの横の大きさ
constexpr int HEART_SIZE_Y = 18;			//ハートの縦の大きさ
constexpr int HEART_NUM = 8;				//ハートの数


//-----------------------------------
//			コンストラクタ
//-----------------------------------
CPlayerStatusPanel::CPlayerStatusPanel()
{
	for (int heartHndl_i = 0; heartHndl_i < HEART_STATE_NUM; heartHndl_i++)
	{
		m_heartHndl.push_back(-1);
	}

	for (int heart_i = 0; heart_i < HEART_STATE_NUM; heart_i++)
	{
		m_heart.push_back(new C2DUi);
	}

	Init();
}

//-----------------------------------
//			  デストラクタ
//-----------------------------------
CPlayerStatusPanel::~CPlayerStatusPanel()
{
	Exit();

	for (int heartHndl_i = 0; heartHndl_i < m_heartHndl.size(); heartHndl_i++)
	{
		if (m_heartHndl[heartHndl_i] == -1)
		{
			DeleteGraph(m_heartHndl[heartHndl_i]);
			m_heartHndl[heartHndl_i] = -1;
		}
	}

	for (int heart_i = 0; heart_i < m_heart.size(); heart_i++)
	{
		m_heart[heart_i]->Exit();
		delete m_heart[heart_i];
	}
	m_heart.clear();

}

//-----------------------------------
//				初期化
//-----------------------------------
void CPlayerStatusPanel::Init()
{
	m_panel.Init();
	m_icon.Init();

	for (int heart_i = 0; heart_i < m_heartHndl.size(); heart_i++)
	{
		m_heartHndl[heart_i] = -1;
	}

}

//-----------------------------------
//			   画像ロード
//-----------------------------------
void CPlayerStatusPanel::Load()
{
	for (int panel_i = 0; panel_i < m_panelHndl.size(); panel_i++)
	{
		if (m_panelHndl[panel_i] == -1)
		{
			m_panelHndl[panel_i] = LoadGraph(GRAPHIC_PANEL_PATH[panel_i]);
		}
	}

	for (int icon_i = 0; icon_i < m_iconHndl.size(); icon_i++)
	{
		if (m_iconHndl[icon_i] == -1)
		{
			m_iconHndl[icon_i] = LoadGraph(GRAPHIC_ICON_PATH[icon_i]);
		}
	}
	if (m_heartHndl[0] == -1)
	{
		LoadDivGraph(GRAPHIC_HEART_PATH, HEART_STATE_NUM, HEART_STATE_NUM, 1,
			HEART_SIZE_X, HEART_SIZE_Y, m_heartHndl.data());
	}
}

//-----------------------------------
//		  毎フレームする処理
//-----------------------------------
void CPlayerStatusPanel::Step()
{

}

//-----------------------------------
//			 描写処理
//-----------------------------------
void CPlayerStatusPanel::Draw()
{

}

//-----------------------------------
//			  終了処理
//-----------------------------------
void CPlayerStatusPanel::Exit()
{

}
