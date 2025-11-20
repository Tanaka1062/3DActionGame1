#include "itemBase.h"

static const float RADIUS = 7.5f;		//半径
static const float ROT_SPEED = 0.05f;	//回転速度

//--------------------------
//	   コンストラクタ
//--------------------------
CItemBase::CItemBase()
{
	Init(nullptr);
}

//--------------------------
//		  初期化
//--------------------------
void CItemBase::Init(CPlayer* _player)
{
	CObject::Init();

	m_rad = RADIUS;
	m_player = _player;
	m_shadow.Init(m_pos,0.5f);
	m_isGravity = true;
}

//--------------------------
//		モデルのロード
//--------------------------
void CItemBase::Load()
{
	CObject::Load();
	m_shadow.Load();
}

//--------------------------
//	 毎フレームする処理
//--------------------------
void CItemBase::Step()
{
	CObject::Step();
	//少しずつ回転させる
	m_rot.y += ROT_SPEED;

	m_shadow.Step(m_pos);
}

//--------------------------
//		  数値の更新
//--------------------------
void CItemBase::Update()
{
	CObject::Update();
	m_shadow.Update();
}

//--------------------------
//		 モデルの描写
//--------------------------
void CItemBase::Draw()
{
	if (m_isActive == false)return;

	CObject::Draw();
	m_shadow.Draw();
}

//--------------------------
//		   終了処理
//--------------------------
void CItemBase::Exit()
{
	CObject::Exit();
	m_shadow.Exit();
}

//--------------------------
//	 使用した時の処理
//--------------------------
void CItemBase::Use()
{

}

//--------------------------
//	  当たった時の処理
//--------------------------
void CItemBase::HitCalc()
{

}
