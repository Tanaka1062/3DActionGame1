#include "characterBase.h"
#include "../../lib/myMath/myMath.h"

static const VECTOR BACK_SPEED = { 0.0f,0.5f,-1.0f };
static const float BACK_DOWN_SPEED = 0.9f;				//速度の減速

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
void CCharacterBase::Init(CAttackManager* _attackManager)
{
	CActor::Init();
	
	m_gravity = 0.0f;
	m_hp = 0;
	m_maxHp = 0;
	m_atk = 0;
	m_rad = 0.0f;
	m_isFlying = false;
	m_isGravity = true;
	m_state = WAIT;
	m_attackManager = _attackManager;
	m_shadow.Init(m_pos,1.0f);
}

//モデルのロード
void CCharacterBase::Load()
{
	CActor::Load();
	m_shadow.Load();
}

//------------------------------
//		毎フレームする処理
//------------------------------
void CCharacterBase::Step()
{
	CActor::Step();

	m_shadow.Step(m_pos);

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

		//回避
	case DODGEROLL:
		Dodgeroll();
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

		//攻撃チャージ前
	case ATTACK_CHARGE_IN:
		AttackChargeIn();
		break;

		//攻撃チャージ
	case ATTACK_CHARGE:
		AttackCharge();
		break;

		//スキル使用前
	case SKILL_IN:
		SkillIn();
		break;

		//スキル使用前
	case SKILL:
		Skill();
		break;

		//スキル使用前
	case SKILL_OUT:
		SkillOut();
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

	m_shadow.Update();

	//Hpが０以下になるとActiveをfalseに
	if (m_hp <= 0 && m_state != DIE)
	{
		m_hp = 0;
		m_state = DIE;
	}

}

//モデルの描写
void CCharacterBase::Draw()
{
	CActor::Draw();
	m_shadow.Draw();
}

//終了処理
void CCharacterBase::Exit()
{
	CActor::Exit();
	delete m_attackManager;
	m_shadow.Exit();
}

//------------------------------
//	攻撃を食らった時にする処理
//------------------------------
void CCharacterBase::HitAttack(int _atk, float _rotY)
{
	//既に怯み状態なら処理をしない
	if (m_state == STAGGER)return;

	//ノックバックの速度を設定------------
	
	//プレイヤーが目の前にいる時に進む速度
	VECTOR defaultDir = BACK_SPEED;
	//上記を行列に変換
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(_rotY);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

	//------------------------------------


	//怯み状態にする
	m_state = STAGGER;
	//Hpを攻撃力分減らす
	m_hp -= _atk;
}

//弾を食らった時にする処理
void CCharacterBase::ShotAttack(int _atk, float _rotY)
{
	HitAttack(_atk, _rotY);
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
//			  回避
//------------------------------
void CCharacterBase::Dodgeroll()
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
//		  攻撃チャージ前
//------------------------------
void CCharacterBase::AttackChargeIn()
{

}

//------------------------------
//		   攻撃チャージ
//------------------------------
void CCharacterBase::AttackCharge()
{

}

//------------------------------
//		  スキル使用前
//------------------------------
void CCharacterBase::SkillIn()
{

}

//------------------------------
//		  スキル使用
//------------------------------
void CCharacterBase::Skill()
{

}

//------------------------------
//		  スキル使用後
//------------------------------
void CCharacterBase::SkillOut()
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
//	 ノックバック処理
//-----------------------
void CCharacterBase::KnockBack()
{
	//速度を徐々に下げていく
	m_speed.x *= BACK_DOWN_SPEED;
	m_speed.z *= BACK_DOWN_SPEED;
	//m_speed = VScale(m_speed, BACK_DOWN_SPEED);
	//一定速度より遅くなったらノックバック
	if (VSize(m_speed) < 0.1f)
	{
		m_state = WAIT;
	}
}

