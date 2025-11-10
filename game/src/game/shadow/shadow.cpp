#include "shadow.h"

static const char* MODEL_PATH =
{ "data/model/shadow/shadow.mv1" };


//初期化
void CShadow::Init(VECTOR _pos, float _scale)
{
	CObject::Init();

	m_pos = _pos;
	m_scale = { _scale,_scale,_scale };
}

//モデルのロード
void CShadow::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = MV1LoadModel(MODEL_PATH);
	}
}

//毎フレームする処理
void CShadow::Step(VECTOR _pos)
{
	m_pos = _pos;
}

