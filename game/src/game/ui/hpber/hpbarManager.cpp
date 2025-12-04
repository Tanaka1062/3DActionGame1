#include "hpbarManager.h"
#include "../../data.h"

static const char MODEL_PATH[] =
{ "data/graphic/ui/hpbar.png" };			//ロードするファイル名

//-------------------------
//	   コンストラクタ
//-------------------------
CHpbarManager::CHpbarManager()
{
	Init();
}

//-------------------------
//		デストラクタ
//-------------------------
CHpbarManager::~CHpbarManager()
{
	Exit();
}

//-------------------------
//		   初期化
//-------------------------
void CHpbarManager::Init(CPlayerManager* _playerManager)
{
	VECTOR pos[PLAYER_NUM] = {
		{315.0f,60.0f,0.0f},
		{static_cast<float>(WINDOW_SIZE_X - 315),60.0f,0.0f},
	};

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_hpbar[i].Init(pos[i]);
		if(_playerManager != nullptr)
		{
			m_hpbar[i].SetPlayer(_playerManager->GetPlayer(i));
		}
	}

	for (int ui_i = 0; ui_i < UI_NUM; ui_i++)
	{
		VECTOR uiPos = ZERO;

		switch (ui_i)
		{
		case PLAYER1_NAME_UI:
			uiPos = pos[0];
			break;
		case PLAYER2_NAME_UI:
			uiPos = pos[1];
			break;
		case VS_UI:
			uiPos.x = WINDOW_SIZE_X * 0.5f;
			uiPos.y = 60.0f;
			break;
		}

		m_ui[ui_i].Init(uiPos);
	}
}

//-------------------------
//		   ロード
//-------------------------
void CHpbarManager::Load()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_hpbar[i].Load(MODEL_PATH);
	}

	const char* UI_GRAPHIC_PATH[UI_NUM] =		//ロードするファイル名
	{
		"data/graphic/ui/player1Name.png",
		"data/graphic/ui/player2Name.png",
		"data/graphic/ui/vs.png",

	};			

	for (int ui_i = 0; ui_i < UI_NUM; ui_i++)
	{
		m_ui[ui_i].Load(UI_GRAPHIC_PATH[ui_i]);
	}

}

//-------------------------
//	 毎フレームする処理
//-------------------------
void CHpbarManager::Step()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_hpbar[i].Step();
	}

}

//-------------------------
//			描写
//-------------------------
void CHpbarManager::Draw()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_hpbar[i].Draw();
	}

	for (int ui_i = 0; ui_i < UI_NUM; ui_i++)
	{
		m_ui[ui_i].Draw();
	}
}

//-------------------------
//			破棄
//-------------------------
void CHpbarManager::Exit()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_hpbar[i].Exit();
	}

	for (int ui_i = 0; ui_i < UI_NUM; ui_i++)
	{
		m_ui[ui_i].Exit();
	}

}

