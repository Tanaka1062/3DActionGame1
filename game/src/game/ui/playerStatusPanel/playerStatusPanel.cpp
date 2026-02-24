#include "playerStatusPanel.h"
#include "../../data.h"

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

constexpr int HEART_SIZE_X = 21;									//ハートの横の大きさ
constexpr int HEART_SIZE_Y = 18;									//ハートの縦の大きさ
constexpr int HEART_NUM = 8;										//ハートの数

constexpr int PANEL_SIZE_X = 320;									//パネルの横の大きさ
constexpr int PANEL_SIZE_Y = 150;									//パネルの縦の大きさ
constexpr VECTOR INIT_POS =											//パネルの初期座標
{ static_cast<float>(PANEL_SIZE_X * 0.5),static_cast<float>(WINDOW_SIZE_Y - PANEL_SIZE_Y * 0.5),0.0f};

//-----------------------------------
//			コンストラクタ
//-----------------------------------
CPlayerStatusPanel::CPlayerStatusPanel()
{
	//ハートの画像ハンドル生成
	for (int heartHndl_i = 0; heartHndl_i < HEART_STATE_NUM; heartHndl_i++)
	{
		m_heartHndl.push_back(-1);
	}

	//配置するハートを生成
	for (int heart_i = 0; heart_i < HEART_NUM; heart_i++)
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

	//ハートの画像を破棄
	for (int heartHndl_i = 0; heartHndl_i < m_heartHndl.size(); heartHndl_i++)
	{
		if (m_heartHndl[heartHndl_i] == -1)
		{
			DeleteGraph(m_heartHndl[heartHndl_i]);
			m_heartHndl[heartHndl_i] = -1;
		}
	}

	//配置するハートを破棄
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
	m_pos = ZERO;

	m_panel.Init();
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
}

//-----------------------------------
//			   画像ロード
//-----------------------------------
void CPlayerStatusPanel::Load(tagPlayerName _playerName)
{
	//中心座標を設定
	m_pos = INIT_POS;
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
	m_icon.Load(GRAPHIC_ICON_PATH[_playerName]);

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
	//現在のプレイヤーの体力を取得する
	float nowHp = static_cast<float>(_player->GetHp());
	float maxHp = static_cast<float>(_player->GetHpMax());
	int heartNum = 0;

	//体力をハートに変換する
	float hp = nowHp / maxHp;
	heartNum = static_cast<int>(hp * (m_heart.size() * (HEART_STATE_NUM - 1)));
	//ハートマイナスにならないようにする
	if (heartNum <= 0)heartNum = 0;

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
}

//-----------------------------------
//			 描写処理
//-----------------------------------
void CPlayerStatusPanel::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);
	m_panel.Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	m_icon.Draw();
	for (int heart_i = 0; heart_i < m_heart.size(); heart_i++)
	{
		m_heart[heart_i]->Draw();
	}
}

//-----------------------------------
//			  終了処理
//-----------------------------------
void CPlayerStatusPanel::Exit()
{
	m_panel.Exit();
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

