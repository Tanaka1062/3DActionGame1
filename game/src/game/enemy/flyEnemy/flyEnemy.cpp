#include "flyEnemy.h"


//攻撃関連---------------------------
static const float ATTACK_SIZE = 7.0f;				//攻撃範囲
static const float ATTACK_LENGTH = 4.0f;			//攻撃の長さ
static const int ATTACK_TIME = 10;					//攻撃の判定の時間(フレーム)
static const int ATTACK_COOL_TIME = 180;			//攻撃のクールタイム(フレーム)
static const float ATTACKABLE_RAD = 12.0f;			//攻撃可能範囲の半径
//-----------------------------------

//----------------
//	   初期化
//----------------
void CFlyEnemy::Init()
{
	CEnemy::Init();
	m_attack.Init(ATTACK_SIZE, ATTACK_LENGTH, ATTACKABLE_RAD);
}

//----------------
//毎フレームする処理
//----------------
void CFlyEnemy::Step(VECTOR _pos)
{
	CEnemy::Step(_pos);

}

//----------------
//	  更新処理
//----------------
void CFlyEnemy::Update()
{
	GravityReset();

	CEnemy::Update();
	m_pos.y = 10.0f;

	VECTOR attackPos = m_attack.GetPos();
	attackPos.y = 5.0f;
	m_attack.SetPos(attackPos);

}

