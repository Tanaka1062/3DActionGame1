#include "characterBase.h"
#include "../../lib/myMath/myMath.h"

constexpr VECTOR KNOCK_BACK_SPEED = { 0.0f,3.0f,-0.8f };
constexpr float BACK_DOWN_SPEED = 0.9f;					//速度の減速
constexpr int BLOWN_MAX = 100;							//吹き飛び最大値

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
	m_hp = 1;
	m_maxHp = 0;
	m_blown = 0;
	m_atk = 0;
	m_rad = 0.0f;
	m_isFlying = false;
	m_isGravity = true;
	m_state = WAIT;
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
void CCharacterBase::Step(CAttackManager* _attackManager, CShotManager* _shotManager)
{
	CActor::Step();

	//被弾中は減らさない
	if (m_state != STAGGER)
	{
		//吹っ飛び蓄積量を少しずつ減らす
		m_blown--;
	}
	//吹っ飛び蓄積量がマイナスにならないようにする
	if (m_blown <= 0)
	{
		m_blown = 0;
	}

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

		//空中
	case AIR:
		Air();
		break;

		//着地
	case LANDING:
		Landing();
		break;

		//攻撃前
	case ATTACK_IN:
		AttackIn();
		break;

		//攻撃
	case ATTACK:
		Attack(_attackManager,_shotManager);
		break;

		//攻撃後
	case ATTACK_OUT:
		AttackOut();
		break;

		//アイテムを持ち上げる
	case ITEM_LIFT_UP:
		ItemLiftUp();
		break;

		//アイテムを下ろす
	case ITEM_PUT_DOWN:
		ItemPutDown();
		break;

		//アイテムを投げる前
	case ITEM_THROW_IN:
		ItemThrowIn();
		break;

		//アイテムを投げる
	case ITEM_THROW:
		ItemThrow();
		break;

		//アイテムを投げた後
	case ITEM_THROW_OUT:
		ItemThrowOut();
		break;

		//怯み
	case STAGGER:
		Stagger();
		break;

		//吹き飛んだ
	case BLOW_AWAY:
		BlowAway();
		break;

		//倒れる
	case DOWN:
		Down();
		break;

		//倒れる前
	case DOWN_IN:
		DownIn();
		break;

		//起き上がる
	case GET_UP:
		GetUp();
		break;

		//死亡
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
	m_shadow.Exit();
}

//------------------------------
//	攻撃を食らった時にする処理
//------------------------------
void CCharacterBase::HitAttack(int _atk, int _blown, float _rotY)
{
	m_blown += _blown;

	VECTOR knockBack = KNOCK_BACK_SPEED;

	if (m_blown >= BLOWN_MAX)
	{
		knockBack = VScale(knockBack, 10.0f);
		m_blown = 0;
		//吹き飛ばし状態にする
		m_state = BLOW_AWAY;
	}
	else
	{
		//怯み状態にする
		m_state = STAGGER;
	}

	//既に怯み状態なら処理をしない
	if (m_state == STAGGER)return;

	//ノックバックの速度を設定------------
	
	//プレイヤーが目の前にいる時に進む速度
	VECTOR defaultDir = knockBack;
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

	//Hpを攻撃力分減らす
	m_hp -= _atk;
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
//				空中
//------------------------------
void CCharacterBase::Air()
{

}

//------------------------------
//				着地
//------------------------------
void CCharacterBase::Landing()
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
void CCharacterBase::Attack(CAttackManager* _attackManager, CShotManager* _shotManager)
{

}

//------------------------------
//			攻撃後
//------------------------------
void CCharacterBase::AttackOut()
{

}

//------------------------------
//	   アイテムを持ち上げる
//------------------------------
void CCharacterBase::ItemLiftUp()
{

}

//------------------------------
//		アイテムを下ろす
//------------------------------
void CCharacterBase::ItemPutDown()
{

}

//------------------------------
//		アイテムを投げる前
//------------------------------
void CCharacterBase::ItemThrowIn()
{

}

//------------------------------
//		アイテムを投げる
//------------------------------
void CCharacterBase::ItemThrow()
{

}

//------------------------------
//		アイテムを投げた後
//------------------------------
void CCharacterBase::ItemThrowOut()
{

}

//------------------------------
//			怯み
//------------------------------
void CCharacterBase::Stagger()
{

}

//------------------------------
//			吹き飛んだ
//------------------------------
void CCharacterBase::BlowAway()
{

}

//------------------------------
//			ダウン前
//------------------------------
void CCharacterBase::DownIn()
{

}

//------------------------------
//			ダウン
//------------------------------
void CCharacterBase::Down()
{

}

//------------------------------
//			起き上がり
//------------------------------
void CCharacterBase::GetUp()
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
	//一定速度より遅くなったらノックバック
	if (VSize(m_speed) <= 0.3f)
	{
		m_state = WAIT;
	}
}

