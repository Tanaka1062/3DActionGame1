#include "flyEnemy.h"

static const int DOWN_TIME = 240;					//ダウンする時間

//攻撃関連---------------------------
static const float ATTACK_SIZE = 12.0f;				//攻撃範囲
static const float ATTACK_LENGTH = 6.0f;			//攻撃の長さ
static const int ATTACK_TIME = 10;					//攻撃の判定の時間(フレーム)
static const int ATTACK_COOL_TIME = 180;			//攻撃のクールタイム(フレーム)
static const float ATTACKABLE_RAD = 11.0f;			//攻撃可能範囲の半径
//-----------------------------------

//----------------
//	   初期化
//----------------
void CFlyEnemy::Init()
{
	CEnemy::Init();
	m_attack.Init(ATTACK_SIZE, ATTACK_LENGTH, ATTACKABLE_RAD);
	m_downTime = DOWN_TIME;
	m_downTimeCount = 0;
	m_isDown = false;
}

//----------------
//毎フレームする処理
//----------------
void CFlyEnemy::Step(VECTOR _pos)
{

	if (m_isDown == true)
	{
		m_downTimeCount++;

		if (m_downTime <= m_downTimeCount)
		{
			m_isDown = false;
			m_downTimeCount = 0;
		}
		Gravity();
	}
	else
	{
		m_pos.y = 13.0f;
	}
	CEnemy::Step(_pos);

	VECTOR attackPos = m_attack.GetPos();
	attackPos.y = 3.0f;
	m_attack.Update(attackPos, m_rot);

}

//----------------
//	  更新処理
//----------------
void CFlyEnemy::Update()
{
	if (m_isDown == false)
	{
		GravityReset();
		m_pos.y = 13.0f;

	}
	else
	{
		m_speed.x = 0.0f;
		m_speed.z = 0.0f;
	}
	CEnemy::Update();
	VECTOR attackPos = m_attack.GetPos();
	attackPos.y = 3.0f;
	m_attack.Update(attackPos, m_rot);

}

//弾を食らった時にする処理
void CFlyEnemy::ShotAttack(int _atk, float _rotY)
{
	if (m_state == STAGGER)return;

	m_isDown = true;


	m_hp -= _atk;
}

