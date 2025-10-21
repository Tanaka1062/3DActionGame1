#include "box.h"


static const char MODEL_PATH[] =
{ "data/model/box/box.mv1" };			//ロードするファイル名

static const int BOX_HP = 50;

//---------------------------
//		  コンストラクタ
//---------------------------
CBox::CBox()
{
	Init();
}

//---------------------------
//		  デストラクタ
//---------------------------
CBox::~CBox()
{
	Exit();
}

//---------------------------
//			初期化
//---------------------------
void CBox::Init()
{
	CObject::Init();
	m_pos = VGet(0.0f, 0.0f, 0.0f);
	m_rad = 6.0f;
	m_hp = BOX_HP;

}

//---------------------------
//		  モデルロード
//---------------------------
void CBox::Load()
{
	CObject::LoadModel(MODEL_PATH);

}

//---------------------------
//		  体力を減らす
//---------------------------
void CBox::SubHp(int _subHp)
{
	m_hp -= _subHp;
}

