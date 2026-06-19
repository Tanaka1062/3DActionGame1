#include "playerStatusPanel.h"
#include "../../data.h"
#include "../../system/number/number.h"

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

enum tagIconState
{
	ICON_NORMAL,							//ノーマルアイコン
	ICON_STAGGER,							//怯みアイコン
	ICON_DIE,								//死亡アイコン
	ICON_ATTACK,							//攻撃アイコン
		
	ICON_STATE_NUM,							//アイコンの状態の数
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

constexpr int ICON_SIZE_X = 88;										//アイコンの横の大きさ
constexpr int ICON_SIZE_Y = 90;										//アイコンの縦の大きさ

constexpr int HEART_SIZE_X = 21;									//ハートの横の大きさ
constexpr int HEART_SIZE_Y = 18;									//ハートの縦の大きさ
constexpr int HEART_NUM = 8;										//ハートの数

constexpr int PANEL_SIZE_X = 320;									//パネルの横の大きさ
constexpr int PANEL_SIZE_Y = 150;									//パネルの縦の大きさ
constexpr VECTOR PANEL_INIT_POS =									//パネルの初期座標
{ static_cast<float>(PANEL_SIZE_X * 0.5),static_cast<float>(WINDOW_SIZE_Y - PANEL_SIZE_Y * 0.5),0.0f};
constexpr int PANEL_BLEND = 200;									//パネルの透明度

constexpr float MONEY_NUMBER_SIZE = 0.5f;							//お金の大きさ
constexpr VECTOR MONEY_NUMBER_INIT_POS = { 70.0f,-40.0f,0.0f };		//お金の初期座標
constexpr int MONEY_DIGIT = 2;										//お金の表示桁数

//-----------------------------------
//			コンストラクタ
//-----------------------------------
CPlayerStatusPanel::CPlayerStatusPanel()
{
	//アイコンの画像ハンドル生成
	for (int iconHndl_i = 0; iconHndl_i < ICON_STATE_NUM; iconHndl_i++)
	{
		m_iconHndl.push_back(-1);
	}

	//ハートの画像ハンドル生成
	for (int heartHndl_i = 0; heartHndl_i < HEART_STATE_NUM; heartHndl_i++)
	{
		m_heartHndl.push_back(-1);
	}

	//配置するハートを生成
	for (int heart_i = 0; heart_i < HEART_NUM; heart_i++)
	{
		m_heart.push_back(unique_ptr<C2DObject>());
	}

	Init();
}

//-----------------------------------
//			  デストラクタ
//-----------------------------------
CPlayerStatusPanel::~CPlayerStatusPanel()
{
	Exit();

	//配置するハートを破棄
	m_heart.clear();
}

//-----------------------------------
//				初期化
//-----------------------------------
void CPlayerStatusPanel::Init()
{
	m_pos = V_ZERO;

	m_panel.Init();

	//アイコンの画像ハンドルを初期化
	for (int iconHndl_i = 0; iconHndl_i < m_iconHndl.size(); iconHndl_i++)
	{
		m_iconHndl[iconHndl_i] = -1;
	}

	m_icon.Init();

	//ハートの画像ハンドルを初期化
	for (int heart_i = 0; heart_i < m_heartHndl.size(); heart_i++)
	{
		m_heartHndl[heart_i] = -1;
	}

	//配置するハートを初期化
	for (int heart_i = 0; heart_i < m_heart.size(); heart_i++)
	{
		m_heart[heart_i]->Init();
	}

	

	m_playerMoney = 0;
}

//-----------------------------------
//			   画像ロード
//-----------------------------------
void CPlayerStatusPanel::Load(tagPlayerName _playerName)
{
	//中心座標を設定
	m_pos = PANEL_INIT_POS;
	//パネルが横一列にならぶように配置をずらす
	m_pos.x += _playerName * PANEL_SIZE_X;
	m_panel.SetPos(m_pos);

	//アイコンの座標を設定
	VECTOR iconPos = m_pos;
	iconPos.x -= 70.0f;
	iconPos.y -= 14.0f;
	m_icon.SetPos(iconPos);

	//ハートの座標を設定
	VECTOR heartPos = m_pos;
	heartPos.x += HEART_SIZE_X;
	for (int heart_i = 0; heart_i < m_heart.size(); heart_i++)
	{
		VECTOR pos = heartPos;
		if (heart_i >= m_heart.size() * 0.5f)
		{
			pos.y += HEART_SIZE_Y;
			pos.x += (heart_i - m_heart.size() * 0.5f) * HEART_SIZE_X;
		}
		else
		{
			pos.x += heart_i * HEART_SIZE_X;
		}
		m_heart[heart_i]->SetPos(pos);
	}

	m_panel.Load(GRAPHIC_PANEL_PATH[_playerName]);

	//アイコンの画像ハンドル読み込み
	if (m_iconHndl[0] == -1)
	{
		LoadDivGraph(GRAPHIC_ICON_PATH[_playerName], ICON_STATE_NUM, ICON_STATE_NUM, 1,
			ICON_SIZE_X, ICON_SIZE_Y, m_iconHndl.data());
	}

	//ハートの画像ハンドル読み込み
	if (m_heartHndl[0] == -1)
	{
		LoadDivGraph(GRAPHIC_HEART_PATH, HEART_STATE_NUM, HEART_STATE_NUM, 1,
			HEART_SIZE_X, HEART_SIZE_Y, m_heartHndl.data());
	}
}

//-----------------------------------
//		  毎フレームする処理
//-----------------------------------
void CPlayerStatusPanel::Step(CPlayer* _player)
{
	//アイコンの変更処理--------------------------------
	tagIconState iconState = ICON_NORMAL;
	switch (_player->GetState())
	{
	case ATTACK:
	case ATTACK_IN:
	case ATTACK_OUT:
		iconState = ICON_ATTACK;
		break;
	case STAGGER:
		iconState = ICON_STAGGER;
		break;
	case DIE:
		iconState = ICON_DIE;
		break;
	}

	m_icon.SetHndl(m_iconHndl[iconState]);
	//--------------------------------------------------

	//現在のプレイヤーの体力を取得する
	float nowHp = static_cast<float>(_player->GetHp());
	float maxHp = static_cast<float>(_player->GetHpMax());
	int heartNum = 0;

	//体力をハートに変換する
	float hp = nowHp / maxHp;
	heartNum = static_cast<int>(hp * (m_heart.size() * (HEART_STATE_NUM - 1)));
	//ハートマイナスにならないようにする
	if (nowHp <= 0)
	{
		heartNum = 0;
	}
	//計算結果がゼロでも体力が残っていたら１にする
	else if (heartNum <= 0)
	{
		heartNum = 1;
	}

	//ハートの状態を入れていく
	for (int heart_i = 0; heart_i < m_heart.size(); heart_i++)
	{
		if (heartNum >= HEART_STATE_NUM - 1)
		{
			m_heart[heart_i]->SetHndl(m_heartHndl[HEART_FULL]);
			heartNum -= HEART_STATE_NUM - 1;
		}
		else
		{
			m_heart[heart_i]->SetHndl(m_heartHndl[heartNum]);
			heartNum = 0;
		}
	}

	m_money = _player->GetMoney();
}

//-----------------------------------
//			 描写処理
//-----------------------------------
void CPlayerStatusPanel::Draw()
{
	//画像の透明度を変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, PANEL_BLEND);
	m_panel.Draw();
	//画像の透明度を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	m_icon.Draw();
	for (int heart_i = 0; heart_i < m_heart.size(); heart_i++)
	{
		m_heart[heart_i]->Draw();
	}

	CNumber::RequestNumber(VAdd(m_pos,MONEY_NUMBER_INIT_POS), m_money, MONEY_NUMBER_SIZE, MONEY_DIGIT);
}

//-----------------------------------
//			  終了処理
//-----------------------------------
void CPlayerStatusPanel::Exit()
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
	for (int heartHndl_i = 0; heartHndl_i < m_heartHndl.size(); heartHndl_i++)
	{
		if (m_heartHndl[heartHndl_i] != -1)
		{
			DeleteGraph(m_heartHndl[heartHndl_i]);
			m_heartHndl[heartHndl_i] = -1;
		}
	}

	for (int heart_i = 0; heart_i < m_heart.size(); heart_i++)
	{
		m_heart[heart_i]->Exit();
	}
}

