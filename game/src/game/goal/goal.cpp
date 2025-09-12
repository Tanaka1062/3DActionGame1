#include"goal.h"

//定義関連---------------------------
static const char MODEL_PATH[] =
{ "data/model/goal/goalTest.mv1" };					//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,1.0f,10.0f };	//初期座標
static const float RADIUS = 5.0f;					//半径
//-----------------------------------

//-----------------
// コンストラクタ
//-----------------
CGoal::CGoal()
{
	Init();
}

//-----------------
//	デストラクタ
//-----------------
CGoal::~CGoal()
{
	Exit();
}

//-----------------
//	   初期化
//-----------------
void CGoal::Init()
{
	CObject::Init();

	m_pos = INIT_POS;
	m_rad = RADIUS;
	m_isGoal = false;
}

//-----------------
//オブジェクトのロード
//-----------------
void CGoal::Load()
{
	CObject::LoadModel(MODEL_PATH);
}

//-----------------
//当たり判定後の処理
//-----------------
void CGoal::HitCalc()
{
	//ゴールしたフラグをtrueに
	m_isGoal = true;
}
