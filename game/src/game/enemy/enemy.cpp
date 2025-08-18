#include "enemy.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
{ "data/model/enemy/enemyTest.mv1" };				//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,1.0f,0.0f };	//初期座標
static const int MAX_HP = 100;						//体力
static const int ATTACK = 10;						//攻撃力
static const float MOVE_SPEED = 2.0f;				//移動スピード
static const float RADIUS = 2.5f;					//半径
static const float FOV_RADIUS = 50.0f;				//視界範囲(半径)
//----------------------------------------------

static const float ATTACK_SIZE = 3.0f;				//攻撃範囲
static const float ATTACK_LENGTH = 2.0f;			//攻撃の長さ
static const int ATTACK_TIME = 120;					//攻撃の判定の時間(フレーム)

//-----------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CEnemy::CEnemy()
{
	Init();
}

//-----------------------
//	デストラクタ
//-----------------------
CEnemy::~CEnemy()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CEnemy::Init()
{
	CCharacterBase::Init();
	m_attack.Init();
	m_FOV.Init(FOV_RADIUS);

	m_pos = INIT_POS;
	m_rad = RADIUS;
	m_hp = MAX_HP;
	m_atk = ATTACK;
}

//-----------------------
//	モデルロード
//-----------------------
void CEnemy::Load()
{
	CActor::LoadModel(MODEL_PATH);
}

//-----------------------
//毎フレームする処理
//-----------------------
void CEnemy::Step()
{
	CCharacterBase::Step();
	//攻撃の毎フレームする処理
	m_attack.Step();
	//視界範囲の毎フレームする処理
	m_FOV.Step();


	//攻撃処理
	if (CheckHitKey(KEY_INPUT_J) != 0 &&
		m_attack.GetActive() == false)
	{
		m_attack.Request(m_pos,m_rot, ATTACK_SIZE, ATTACK_LENGTH, ATTACK_TIME);
	}

	//攻撃の更新
	m_attack.Update(m_pos, m_rot);
	//視界範囲の更新
	m_FOV.Update(m_pos);

}

//-----------------------
//		描写処理
//-----------------------
void CEnemy::Draw()
{
	CCharacterBase::Draw();

#ifdef DEBUG

	DrawSphere3D(GetCenter(), m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

	//DrawSphere3D(GetCenter(), FOV_RADIUS, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG
	
}

//-----------------------
//		待機処理
//-----------------------
void CEnemy::Wait()
{

}

//-----------------------
//		歩く処理
//-----------------------
void CEnemy::Walk()
{

}

//-----------------------
//		ジャンプ
//-----------------------
void CEnemy::Jump()
{

}

//-----------------------
//		攻撃
//-----------------------
void CEnemy::Attack()
{

}

//-----------------------
//		怯み
//-----------------------
void CEnemy::Stagger()
{

}

//-----------------------
//		移動処理
//-----------------------
void CEnemy::Move(float _rotY)
{

}

