#include "hpbarManager.h"
#include "../../data.h"

static const char MODEL_PATH[] =
{ "data/graphic/ui/Hpbar.png" };			//ロードするファイル名

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
		{315.0f,100.0f,0.0f},
		{static_cast<float>(WINDOW_SIZE_X - 100),100.0f,0.0f},
	};

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_hpbar[i].Init(pos[i]);
		if(_playerManager != nullptr)
		{
			m_hpbar[i].SetPlayer(_playerManager->GetPlayer(i));
		}
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
}

