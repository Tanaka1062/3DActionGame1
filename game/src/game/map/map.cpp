#include "map.h"
#include <math.h>

//定義関連==================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };		//大きさ
static const char GROUND_MODEL_PATH[] =
 "data/model/map/TestMap6.mv1" ;					//ロードするファイル名
static const char GROUND_HIT_MODEL_PATH[] =
 "data/model/map/TestMap6Hit.mv1" ;				//ロードするファイル名

//==========================================


//------------------------
//	コンストラクタ
//------------------------
CMap::CMap()
{
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
	CObject::Init();
	m_pos = ZERO;
	m_scale = SCALE;
	m_rot = ZERO;
	m_hndl = -1;
	m_hitHndl = -1;
}

//------------------------
//		モデルロード
//------------------------
void CMap::Load()
{
	LoadModel(GROUND_MODEL_PATH);

	m_hitHndl = MV1LoadModel(GROUND_HIT_MODEL_PATH);

	//マップの当たり判定を取るためにコリジョン情報を構築する
	MV1SetupCollInfo(m_hitHndl);
}

//------------------------
//		モデル描写
//------------------------
void CMap::Draw()
{
	CObject::Draw();

}

