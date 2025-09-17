#include "map.h"
#include <math.h>

//定義関連==================================
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const VECTOR SCALE = { 0.1f,0.1f,0.1f };		//大きさ
static const char GROUND_MODEL_PATH[] =
{ "data/model/map/testMap.mv1" };					//ロードするファイル名
//==========================================


//------------------------
//	コンストラクタ
//------------------------
CMap::CMap()
{
	CObject::Init();
	Init();
}

//------------------------
//	デストラクタ
//------------------------
CMap::~CMap()
{
	Exit();
}

//------------------------
//		初期化
//------------------------
void CMap::Init()
{
	m_pos = ZERO;
	m_scale = SCALE;
	m_rot = ZERO;
	m_hndl = -1;

}

//------------------------
//		モデルロード
//------------------------
void CMap::Load()
{
	LoadModel(GROUND_MODEL_PATH);

	//マップの当たり判定を取るためにコリジョン情報を構築する
	MV1SetupCollInfo(m_hndl);
}

//------------------------
//		モデル描写
//------------------------
void CMap::Draw()
{
	CObject::Draw();
}

