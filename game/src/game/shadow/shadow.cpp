#include "shadow.h"

static const char* MODEL_PATH =
 "data/model/shadow/shadow.mv1" ;


//初期化
void CShadow::Init(VECTOR _pos, float _scale)
{
	CObject::Init();

	m_pos = _pos;
	m_pos.y += 1.0f;
	m_scale = { _scale,_scale,_scale };
	m_isPosUpdate = false;
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
	m_pos.x = _pos.x;
	m_pos.z = _pos.z;

	m_isPosUpdate = false;
}

