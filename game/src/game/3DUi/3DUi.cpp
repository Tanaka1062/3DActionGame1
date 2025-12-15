#include "3DUi.h"

static const float POS_Y_UP = 19.0f;		//どれくらい上に上がるか
static const char* MODEL_PATH =
{"data/model/3DUi/3DUi.mv1"};


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

}

//モデルロード
void C3DUi::Load()
{
	CObject::LoadModel(MODEL_PATH);
}

//毎フレームする処理
void C3DUi::Step(VECTOR _pos, float _rad,float _cameraRotY, int _money)
{
	m_pos = _pos;

	m_pos.y += (_rad * 2) + POS_Y_UP;

	CObject::Step();

	m_rot.y = _cameraRotY;
}
