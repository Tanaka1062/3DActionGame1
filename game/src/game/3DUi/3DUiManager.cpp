#include "3DUiManager.h"

C3DUiManager* C3DUiManager::m_instance = nullptr;

using namespace std;

constexpr int UI_MAX_NUM = 10;			//UIの数

constexpr const char* MATERIAL_PATH[MT_NUM] =
{
	"data/material/3DUi/crown.png",
	"data/material/3DUi/player1Name.png",
	"data/material/3DUi/player2Name.png",
	"data/material/3DUi/player3Name.png",
	"data/material/3DUi/player4Name.png",
	"data/material/3DUi/cpuName.png",

};

//------------------------
//	    コンストラクタ
//------------------------
C3DUiManager::C3DUiManager()
{
	for (int ui_i = 0; ui_i < UI_MAX_NUM; ui_i++)
	{
		m_3DUi.push_back(make_unique<C3DUi>());
	}

	Init();
}

//------------------------
//		デストラクタ
//------------------------
C3DUiManager::~C3DUiManager()
{
	Exit();

	m_3DUi.clear();
}

//------------------------
//		  初期化
//------------------------
void C3DUiManager::Init()
{
	for (int ui_i = 0; ui_i < m_3DUi.size(); ui_i++)
	{
		m_3DUi[ui_i]->Init();
	}
}

//------------------------
//		 描画処理
//------------------------
void C3DUiManager::Draw()
{
	if (m_instance == nullptr)return;

	for (int ui_i = 0; ui_i < m_3DUi.size(); ui_i++)
	{
		m_3DUi[ui_i]->Draw();
	}
}

//------------------------
//		 終了処理
//------------------------
void C3DUiManager::Exit()
{
	for (int ui_i = 0; ui_i < m_3DUi.size(); ui_i++)
	{
		m_3DUi[ui_i]->Exit();
	}
}

//------------------------
//	ロードの呼び出し処理
//------------------------
int C3DUiManager::RequsetLoad(int _3DUiId)
{
	for (int ui_i = 0; ui_i < m_3DUi.size(); ui_i++)
	{
		if (m_3DUi[ui_i]->GetHndl() == -1)
		{
			m_3DUi[ui_i]->Load(MATERIAL_PATH[_3DUiId]);
			return ui_i;
		}
	}

	unique_ptr<C3DUi> ui = make_unique<C3DUi>();
	ui->Init();
	ui->Load(MATERIAL_PATH[_3DUiId]);
	m_3DUi.push_back(move(ui));

	return static_cast<int>(m_3DUi.size() - 1);
}

