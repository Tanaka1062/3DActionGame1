#include "box.h"

static const int   HP = 50;			//体力
static const float RADIUS = 10.0f;	//半径

//アニメーション一覧---------------------------
enum tagAnim {
	ANIMID_DEFAULT,					//デフォルトのアニメーション
	ANIMID_HIT,						//攻撃を受けた時のアニメーション
};
//---------------------------------------------

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
	CActor::Init();
	m_pos = VGet(0.0f, 0.0f, 0.0f);
	m_rad = RADIUS;
	m_hp = HP;
	m_gravity = 0.0f;
}

//---------------------------
//		  モデルロード
//---------------------------
void CBox::Load(int _modelHndl)
{
	CActor::DuplicateModel(_modelHndl);

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

	CActor::Update();

	//速度をリセット
	m_speed = { 0.0f,0.0f,0.0f };
}

//---------------------------
//		  体力を減らす
//---------------------------
void CBox::SubHp(int _subHp)
{
	m_hp -= _subHp;

	Request(ANIMID_HIT, 1.0f);
}

//---------------------------
//		   重力処理
//---------------------------
void CBox::Gravity()
{
	m_gravity += 0.09f;
}
