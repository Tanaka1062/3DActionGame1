#include "3DUi.h"

using namespace std;

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

constexpr float POS_Y_UP = 19.0f;		//どれくらい上に上がるか
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

	m_materialHndl.clear();
}

//--------------------------
//		モデルロード
//--------------------------
void C3DUi::Load()
{
	//マテリアルをロード
	for (int material_i = 0; material_i < MT_NUM; material_i++)
	{
		int hndl = LoadGraph(MATERIAL_PATH[material_i]);

		m_materialHndl.push_back(hndl);
	}

	//モデルをロード
	CObject::LoadModel(MODEL_PATH);

	//マテリアルをモデルにセット
	MV1SetTextureGraphHandle(m_hndl, MODEL_ICON, m_materialHndl[MT_CROWN], FALSE);
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
//		   終了処理
//--------------------------
void C3DUi::Exit()
{
	CObject::Exit();

	for (int i = 0; i < m_materialHndl.size(); i++)
	{
		DeleteGraph(m_materialHndl[i]);
	}
}

