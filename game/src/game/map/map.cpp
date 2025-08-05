#include "map.h"
#include <math.h>

//定義関連==================================
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const VECTOR SCALE = { 0.1f,0.1f,0.1f };		//大きさ
//==========================================

//コンストラクタ
CGround::CGround()
{
	CObject::Init();
	Init();
}
//デストラクタ
CGround::~CGround()
{
	Exit();
}


//初期化
void CGround::Init()
{
	m_pos = ZERO;
	m_scale = SCALE;
	m_rot = ZERO;
	m_hndl = -1;

}



