#include "moveBlock.h"

constexpr VECTOR BLOCK_SIZE = {130.0f,13.0f,190.0f};	//ブロックの大きさ
constexpr int MAP_FRAME_NUM = 79;						//マップのフレーム番号

//--------------------------
//		コンストラクタ
//--------------------------
CMoveBlock::CMoveBlock()
{
	Init();
}

//--------------------------
//		デストラクタ
//--------------------------
CMoveBlock::~CMoveBlock()
{
	CObject::Exit();
}

//--------------------------
//			初期化
//--------------------------
void CMoveBlock::Init()
{
	CObject::Init();
	m_isActive = false;
	m_objectType = OBJECT_TYPE_BOX;
	m_size = BLOCK_SIZE;
}

//--------------------------
//	  毎フレームする処理
//--------------------------
void CMoveBlock::Step()
{

}
