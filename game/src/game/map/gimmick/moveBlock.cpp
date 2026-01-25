#include "moveBlock.h"
#include "../map.h"

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
	m_objectType = OBJECT_TYPE_BOX;
	m_size = BLOCK_SIZE;
}

//--------------------------
//		モデルロード
//--------------------------
void CMoveBlock::Load(const char* _filePath)
{
	CObject::LoadModel(_filePath);

	int mapFrameHndl = MV1LoadModel(MAP_FRAME_PATH[MAP_ID_GRASSLAND]);

	m_pos = MV1GetFramePosition(mapFrameHndl, MAP_FRAME_NUM);
}

//--------------------------
//	  毎フレームする処理
//--------------------------
void CMoveBlock::Step()
{

}
