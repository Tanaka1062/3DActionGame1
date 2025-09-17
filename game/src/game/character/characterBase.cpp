#include "characterBase.h"

//------------------------------
//		コンストラクタ
//------------------------------
CCharacterBase::CCharacterBase()
{
	Init();
}

//------------------------------
//			初期化
//------------------------------
void CCharacterBase::Init()
{
	CActor::Init();
	
	m_gravity = 0.0f;
	m_hp = 0;
	m_atk = 0;
	m_rad = 0;
	m_state = WAIT;
}

//初期化(弾を出すキャラ用)
void CCharacterBase::Init(CShotManager* _shot)
{
	Init();
	m_shot = _shot;
}

//------------------------------
//		毎フレームする処理
//------------------------------
void CCharacterBase::Step()
{
	//重力処理
	Gravity();

	//状態によって行動を変える
	switch (m_state)
	{
		//待機処理
	case WAIT:
		Wait();
		break;

		//歩く処理
	case WALK:
		Walk();
		break;

		//ジャンプ
	case JUMP:
		Jump();
		break;

		//攻撃前
	case ATTACK_IN:
		AttackIn();
		break;

		//攻撃
	case ATTACK:
		Attack();
		break;

		//攻撃後
	case ATTACK_OUT:
		AttackOut();
		break;

		//アイテム前
	case ITEM_USE_IN:
		ItemUseIn();
		break;

		//アイテム中
	case ITEM_USE:
		ItemUse();
		break;

		//アイテム後
	case ITEM_USE_OUT:
		ItemUseOut();
		break;

		//怯み
	case STAGGER:
		Stagger();
		break;

	case DIE:
		Die();
		break;
	}

}

//------------------------------
//毎フレームする処理(座標取得用)
//------------------------------
void CCharacterBase::Step(VECTOR _pos)
{

}

//------------------------------
//			数値の更新
//------------------------------
void CCharacterBase::Update()
{
	CActor::Update();

	m_speed.y -= m_gravity;

	//Hpが０以下になるとActiveをfalseに
	if (m_hp <= 0 && m_state != DIE)
	{
		m_hp = 0;
		m_state = DIE;
	}

}

//------------------------------
//	攻撃を食らった時にする処理
//------------------------------
void CCharacterBase::HitAttack(int _atk)
{
	//既に怯み状態なら処理をしない
	if (m_state == STAGGER)return;

	//怯み状態にする
	m_state = STAGGER;
	//Hpを攻撃力分減らす
	m_hp -= _atk;
}

//------------------------------
//		重力リセット
//------------------------------
void CCharacterBase::GravityReset()
{
	m_gravity = 0.0f;
}

//------------------------------
//			待機処理
//------------------------------
void CCharacterBase::Wait()
{

}

//------------------------------
//			歩く処理
//------------------------------
void CCharacterBase::Walk()
{

}

//------------------------------
//			ジャンプ
//------------------------------
void CCharacterBase::Jump()
{

}

//------------------------------
//			攻撃前
//------------------------------
void CCharacterBase::AttackIn()
{

}

//------------------------------
//			攻撃中
//------------------------------
void CCharacterBase::Attack()
{

}

//------------------------------
//			攻撃後
//------------------------------
void CCharacterBase::AttackOut()
{

}

//------------------------------
//		アイテム使用前
//------------------------------
void CCharacterBase::ItemUseIn()
{

}

//------------------------------
//		アイテム使用中
//------------------------------
void CCharacterBase::ItemUse()
{

}

//------------------------------
//		アイテム使用後
//------------------------------
void CCharacterBase::ItemUseOut()
{

}

//------------------------------
//			怯み
//------------------------------
void CCharacterBase::Stagger()
{

}

//------------------------------
//			死亡
//------------------------------
void CCharacterBase::Die()
{

}

//-----------------------
//		重力処理
//-----------------------
void CCharacterBase::Gravity()
{
	m_gravity += 0.09f;

}

