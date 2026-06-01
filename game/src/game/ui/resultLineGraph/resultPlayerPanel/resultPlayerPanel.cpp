#include "resultPlayerPanel.h"
#include "../../../data.h"
#include "../../../system/number/number.h"

using namespace std;

namespace {
	//パネルの名前
	enum tagPlayerStatusPanel
	{
		PANEL_PLAYER1,							//プレイヤー1のパネル
		PANEL_PLAYER2,							//プレイヤー2のパネル
		PANEL_PLAYER3,							//プレイヤー3のパネル
		PANEL_PLAYER4,							//プレイヤー4のパネル

		PANEL_NUM,								//パネルの数
	};

	enum tagIconState
	{
		ICON_NORMAL,							//ノーマルアイコン
		ICON_STAGGER,							//怯みアイコン
		ICON_DIE,								//死亡アイコン
		ICON_ATTACK,							//攻撃アイコン

		ICON_STATE_NUM,							//アイコンの状態の数
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

	constexpr float SCALE = 0.7f;										//大きさ

	constexpr int ICON_SIZE_X = 88;										//アイコンの横の大きさ
	constexpr int ICON_SIZE_Y = 90;										//アイコンの縦の大きさ
	constexpr VECTOR ICON_INIT_POS = { 51.0f,10.0f,0.0f };				//アイコンの初期座標

	constexpr int PANEL_SIZE_X = 320;									//パネルの横の大きさ
	constexpr int PANEL_SIZE_Y = 150;									//パネルの縦の大きさ
	constexpr int PANEL_BLEND = 200;									//パネルの透明度

	constexpr float MONEY_NUMBER_SIZE = 0.5f;							//お金の大きさ
	constexpr VECTOR MONEY_NUMBER_INIT_POS = { 58.0f,-25.0f,0.0f };		//お金の初期座標
	constexpr int MONEY_DIGIT = 2;										//お金の表示桁数

}

//-----------------------------------
//			コンストラクタ
//-----------------------------------
CResultPlayerPanel::CResultPlayerPanel()
{
	//アイコンの画像ハンドル生成
	for (int iconHndl_i = 0; iconHndl_i < ICON_STATE_NUM; iconHndl_i++)
	{
		m_iconHndl.push_back(-1);
	}

	Init();
}

//-----------------------------------
//			  デストラクタ
//-----------------------------------
CResultPlayerPanel::~CResultPlayerPanel()
{
	Exit();
}

//-----------------------------------
//				初期化
//-----------------------------------
void CResultPlayerPanel::Init()
{
	m_pos = ZERO;

	m_panel.Init();

	//アイコンの画像ハンドルを初期化
	for (int iconHndl_i = 0; iconHndl_i < m_iconHndl.size(); iconHndl_i++)
	{
		m_iconHndl[iconHndl_i] = -1;
	}

	m_icon.Init();

	m_playerMoney = 0;
}

//-----------------------------------
//			   画像ロード
//-----------------------------------
void CResultPlayerPanel::Load(tagPlayerName _playerName, VECTOR _pos,int _money)
{
	//中心座標を設定
	m_pos = _pos;
	m_panel.SetPos(m_pos);

	//アイコンの座標を設定
	VECTOR iconPos =VSub(m_pos,ICON_INIT_POS);
	m_icon.SetPos(iconPos);

	m_panel.Load(GRAPHIC_PANEL_PATH[_playerName]);

	m_icon.Load(GRAPHIC_ICON_PATH[_playerName], ICON_STATE_NUM, ICON_SIZE_X, ICON_SIZE_Y);
	//アイコンの画像ハンドル読み込み
	if (m_iconHndl[0] == -1)
	{
		LoadDivGraph(GRAPHIC_ICON_PATH[_playerName], ICON_STATE_NUM, ICON_STATE_NUM, 1,
			ICON_SIZE_X, ICON_SIZE_Y, m_iconHndl.data());
	}

	m_money = _money;
}

//-----------------------------------
//			 描写処理
//-----------------------------------
void CResultPlayerPanel::Draw()
{
	//画像の透明度を変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, PANEL_BLEND);
	m_panel.Draw(SCALE);
	//画像の透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	m_icon.Draw(SCALE);

	CNumber::RequestNumber(VAdd(m_pos,MONEY_NUMBER_INIT_POS), m_money, MONEY_NUMBER_SIZE, MONEY_DIGIT);
}

//-----------------------------------
//			  終了処理
//-----------------------------------
void CResultPlayerPanel::Exit()
{
	m_panel.Exit();

	for (int iconHndl_i = 0; iconHndl_i < m_iconHndl.size(); iconHndl_i++)
	{
		if (m_iconHndl[iconHndl_i] != -1)
		{
			DeleteGraph(m_iconHndl[iconHndl_i]);
			m_iconHndl[iconHndl_i] = -1;
		}
	}

	m_icon.Exit();
}

