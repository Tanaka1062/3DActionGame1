#include "3DUi.h"
#include "../camera/cameraManager.h"

using namespace std;

enum tagMaterialName
{
	MT_NUMBER0,		//ナンバー0
	MT_NUMBER1,		//ナンバー1
	MT_NUMBER2,		//ナンバー2
	MT_NUMBER3,		//ナンバー3
	MT_NUMBER4,		//ナンバー4
	MT_NUMBER5,		//ナンバー5
	MT_NUMBER6,		//ナンバー6
	MT_NUMBER7,		//ナンバー7
	MT_NUMBER8,		//ナンバー8
	MT_NUMBER9,		//ナンバー9
	MT_COIN,		//お金
	MT_MINUS_COIN,	//引かれるお金

	MT_NUM,			//ナンバーの数
};

enum tagModelName
{
	MODEL_ICON,		//アイコン
	MODEL_TEN,		//十の位
	MODEL_ONE,		//一の位

	MODEL_NUM,		//モデルの数
};

constexpr float POS_Y_UP = 19.0f;		//どれくらい上に上がるか
static const char* MODEL_PATH =
"data/model/3DUi/3DUi.mv1";

static const char* MATERIAL_PATH[MT_NUM] =
{
	"data/material/3DUi/number0Body.png",
	"data/material/3DUi/number1Body.png",
	"data/material/3DUi/number2Body.png",
	"data/material/3DUi/number3Body.png",
	"data/material/3DUi/number4Body.png",
	"data/material/3DUi/number5Body.png",
	"data/material/3DUi/number6Body.png",
	"data/material/3DUi/number7Body.png",
	"data/material/3DUi/number8Body.png",
	"data/material/3DUi/number9Body.png",
	"data/material/3DUi/coinUi.png",
	"data/material/3DUi/minusCoinUi.png",
};

C3DUi::C3DUi()
{
	CObject::Init();
}

C3DUi::~C3DUi()
{
	CObject::Exit();
}

//初期化
void C3DUi::Init()
{
	CObject::Init();

	m_materialHndl.clear();
}

//モデルロード
void C3DUi::Load()
{
	for (int material_i = 0; material_i < MT_NUM; material_i++)
	{
		int hndl = LoadGraph(MATERIAL_PATH[material_i]);

		m_materialHndl.push_back(hndl);
	}

	CObject::LoadModel(MODEL_PATH);
}

//毎フレームする処理
void C3DUi::Step(VECTOR _pos, float _rad, int _money, tag3DUiType _type)
{
	switch (_type)
	{
	case UI_TYPE_COIN:
		MV1SetTextureGraphHandle(m_hndl, MODEL_ICON, m_materialHndl[MT_COIN], FALSE);
		break;
	case UI_TYPE_COIN_COST:
		MV1SetTextureGraphHandle(m_hndl, MODEL_ICON, m_materialHndl[MT_MINUS_COIN], FALSE);
		break;
	default:
		break;
	}

	m_pos = _pos;

	m_pos.y += (_rad * 2) + POS_Y_UP;

	CObject::Step();

	m_rot.y = CCameraManager::GetRot().y;

	int ten = _money / 10;
	int one = _money % 10;

	MV1SetTextureGraphHandle(m_hndl,MODEL_TEN,m_materialHndl[ten],FALSE);
	MV1SetTextureGraphHandle(m_hndl, MODEL_ONE, m_materialHndl[one], FALSE);
}
