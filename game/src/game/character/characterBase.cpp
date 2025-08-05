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

	m_hp = 0;
	m_attack = 0;
	m_state = WAIT;
}

//------------------------------
//		毎フレームする処理
//------------------------------
void CCharacterBase::Step()
{
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

		//攻撃
	case ATTACK:
		Attack();
		break;

		//怯み
	case STAGGER:
		Stagger();
		break;
	}

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
//			攻撃
//------------------------------
void CCharacterBase::Attack()
{

}

//------------------------------
//			怯み
//------------------------------
void CCharacterBase::Stagger()
{

}
