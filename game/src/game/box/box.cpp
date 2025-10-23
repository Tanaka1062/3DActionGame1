#include "box.h"


static const char MODEL_PATH[] =
{ "data/model/box/box.mv1" };			//ロードするファイル名

static const int BOX_HP = 50;

static const VECTOR BOX_SIZE = { 10.0f,10.0f,10.0f };

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
	m_gravity = 0.0f;
	m_size = BOX_SIZE;
}

//---------------------------
//		  モデルロード
//---------------------------
void CBox::Load()
{
	CObject::LoadModel(MODEL_PATH);

}

//---------------------------
//	   毎フレームする処理
//---------------------------
void CBox::Step()
{
	//重力処理
	Gravity();

	//体力が0以下なら壊れる
	if (m_hp <= 0)
	{
		m_isActive = false;
	}
}

//---------------------------
//		   数値の更新
//---------------------------
void CBox::Update()
{
	//重力を速度に加算
	m_speed.y -= m_gravity;

	CObject::Update();

	//速度をリセット
	m_speed = { 0.0f,0.0f,0.0f };
}

//---------------------------
//		 中心座標を取得
//---------------------------
VECTOR CBox::GetCenter()
{
	//中心座標保存用
	VECTOR center = m_pos;

	//高さの半分を足す
	center.y += (m_size.y * 0.5f);

	return center;
}

//---------------------------
//		  体力を減らす
//---------------------------
void CBox::SubHp(int _subHp)
{
	m_hp -= _subHp;
}

//---------------------------
//		   重力処理
//---------------------------
void CBox::Gravity()
{
	m_gravity += 0.09f;
}
