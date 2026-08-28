#include "3DUi.h"

constexpr float POS_Y_UP		= 19.0f;			//どれくらい上に上がるか
constexpr float MATERIAL_SIZE	= 25.6f;		


//--------------------------
//		コンストラクタ
//--------------------------
C3DUi::C3DUi()
{
	Init();
}

//--------------------------
//		デストラクタ
//--------------------------
C3DUi::~C3DUi()
{
	Exit();
}

//--------------------------
//		   初期化
//--------------------------
void C3DUi::Init()
{
	m_hndl = -1;
}

//--------------------------
//		モデルロード
//--------------------------
void C3DUi::Load(const char* _filePath)
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph(_filePath);
	}
}

//--------------------------
//		  描写処理
//--------------------------
void C3DUi::Draw()
{
	if (m_isActive == false)return;

	float half = MATERIAL_SIZE * 0.5f;
	DrawModiBillboard3D(m_pos, -half, half, half, half, half, -half, -half, -half, m_hndl, TRUE);
}

//--------------------------
//		   終了処理
//--------------------------
void C3DUi::Exit()
{
	if (m_hndl != -1)
	{
		DeleteGraph(m_hndl);
		m_hndl = -1;
	}
}

