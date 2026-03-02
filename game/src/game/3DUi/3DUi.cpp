#include "3DUi.h"

enum tagMaterialName
{
	MT_CROWN,		//王冠

	MT_NUM,			//ナンバーの数
};

enum tagModelName
{
	MODEL_ICON,		//アイコン

	MODEL_NUM,		//モデルの数
};

constexpr float POS_Y_UP = 19.0f;			//どれくらい上に上がるか
constexpr float MATERIAL_SIZE = 12.8f;		
static const char* MODEL_PATH =
"data/model/3DUi/3DUi.mv1";

static const char* MATERIAL_PATH[MT_NUM] =
{
	"data/material/3DUi/crown.png",
};

//--------------------------
//		コンストラクタ
//--------------------------
C3DUi::C3DUi()
{
	CObject::Init();
}

//--------------------------
//		デストラクタ
//--------------------------
C3DUi::~C3DUi()
{
	CObject::Exit();
}

//--------------------------
//		   初期化
//--------------------------
void C3DUi::Init()
{
	CObject::Init();
}

//--------------------------
//		モデルロード
//--------------------------
void C3DUi::Load()
{
	//マテリアルをロード
	m_materialHndl = LoadGraph(MATERIAL_PATH[MT_CROWN]);


	//モデルをロード
	CObject::LoadModel(MODEL_PATH);
}

//--------------------------
//	 毎フレームする処理
//--------------------------
void C3DUi::Step(VECTOR _pos, float _rad, float _cameraRotY)
{

	m_pos = _pos;

	m_pos.y += (_rad * 2) + POS_Y_UP;

	CObject::Step();

	m_rot.y = _cameraRotY;

}

//--------------------------
//		  描写処理
//--------------------------
void C3DUi::Draw()
{
	if (m_isActive == false)return;

	float half = MATERIAL_SIZE * 0.5f;
	DrawModiBillboard3D(m_pos, half, half, -half, half, -half, -half, half, -half, m_materialHndl, TRUE);
}

//--------------------------
//		   終了処理
//--------------------------
void C3DUi::Exit()
{
	CObject::Exit();

	if (m_materialHndl != -1)
	{
		DeleteGraph(m_materialHndl);
		m_materialHndl = -1;
	}
}

