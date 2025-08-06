#include "player.h"
#include "../data.h"

//定義関連---------------------------
static const char MODEL_PATH[] =
{ "data/model/player/playerTest.mv1" };				//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,10.0f,0.0f };	//初期座標
static const int MAX_HP = 100;						//体力
static const int ATTACK = 10;						//攻撃力
//-----------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CPlayer::CPlayer()
{
	Init();
}

//-----------------------
//	デストラクタ
//-----------------------
CPlayer::~CPlayer()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CPlayer::Init()
{
	CCharacterBase::Init();

	m_pos = INIT_POS;
	m_hp = MAX_HP;
	m_attack = ATTACK;
}

//-----------------------
//	モデルロード
//-----------------------
void CPlayer::Load()
{
	CActor::LoadModel(MODEL_PATH);
}

//-----------------------
//毎フレームする処理
//-----------------------
void CPlayer::Step()
{
	CCharacterBase::Step();

}

//-----------------------
//		待機処理
//-----------------------
void CPlayer::Wait()
{

}

//-----------------------
//		歩く処理
//-----------------------
void CPlayer::Walk()
{

}

//-----------------------
//		ジャンプ
//-----------------------
void CPlayer::Jump()
{

}

//-----------------------
//		攻撃
//-----------------------
void CPlayer::Attack()
{

}

//-----------------------
//		怯み
//-----------------------
void CPlayer::Stagger()
{

}

//-----------------------
//		移動処理
//-----------------------
void CPlayer::Move()
{

}
