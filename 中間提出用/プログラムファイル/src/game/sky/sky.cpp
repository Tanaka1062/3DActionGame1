#include "sky.h"

//定義関連==================================
static const float ALL_SCALE = 18.0f;
static const VECTOR SCALE = VGet(ALL_SCALE, ALL_SCALE, ALL_SCALE);
static const float ROTATE_SPEED = 0.1f;				//回転速度
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const char SKY_MODEL_PATH[] =
{ "data/model/sky/sky.mv1" };	//ロードするファイル名
//==========================================

//---------------------------
//		コンストラクタ
//---------------------------
CSky::CSky()
{
	CObject::Init();
	Init();
}

//---------------------------
//		デストラクタ
//---------------------------
CSky::~CSky()
{
	Exit();
}

//---------------------------
//		初期化
//---------------------------
void CSky::Init()
{
	m_pos = ZERO;
	m_scale = SCALE;
	m_rot = ZERO;
	m_hndl = -1;

}

//---------------------------
//		画像ロード
//---------------------------
void CSky::Load()
{
	LoadModel(SKY_MODEL_PATH);
}

//---------------------------
//	毎フレームする処理
//---------------------------
void CSky::Step()
{
	//プレイヤーの回転
	Rotate();

}

//---------------------------
//			回転
//---------------------------
void CSky::Rotate()
{
	m_rot.y += 0.0005f;
}

