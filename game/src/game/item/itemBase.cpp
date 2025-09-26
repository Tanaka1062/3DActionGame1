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

	m_name = ITEM_NONE;
	m_type = TYPE_NONE;
	m_player = _player;
}

//--------------------------
//	 毎フレームする処理
//--------------------------
void CItemBase::Step()
{
	//少しずつ回転させる
	m_rot.y += ROT_SPEED;
}

//--------------------------
//	 使用した時の処理
//--------------------------
void CItemBase::Use()
{

}

