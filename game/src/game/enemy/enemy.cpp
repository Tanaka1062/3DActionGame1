#include "enemy.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
{ "data/model/enemy/enemyTest1.mv1" };				//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,1.0f,0.0f };	//初期座標
static const int MAX_HP = 100;						//体力
static const int ATK = 1;							//攻撃力
static const float MOVE_SPEED = 0.25f;				//移動スピード
static const float RADIUS = 2.5f;					//半径
static const float FOV_RADIUS = 50.0f;				//視界範囲(半径)
//----------------------------------------------

//攻撃関連---------------------------
static const float ATTACK_SIZE = 3.0f;				//攻撃範囲
static const float ATTACK_LENGTH = 4.0f;			//攻撃の長さ
static const int ATTACK_TIME = 10;					//攻撃の判定の時間(フレーム)
static const int ATTACK_COOL_TIME = 180;			//攻撃のクールタイム(フレーム)
static const float ATTACKABLE_RAD = 5.0f;			//攻撃可能範囲の半径
//-----------------------------------

//アニメーション一覧---------------------------
enum tagAnim {
	ANIMID_ATTACK,			//攻撃中アニメーション
	ANIMID_ATTACK_IN,		//攻撃前のアニメーション
	ANIMID_ATTACK_OUT,		//攻撃後のアニメーション
	ANIMID_DEFAULT,			//デフォルトのアニメーション
	ANIMID_HIT,				//被弾のアニメーション
	ANIMID_ITEM_USE,		//アイテムを使用中のアニメーション
	ANIMID_ITEM_USE_IN,		//アイテムを使用する前のアニメーション
	ANIMID_ITEM_USE_OUT,	//アイテムを使用した後のアニメーション
	ANIMID_WAIT,			//待機状態のアニメーション
	ANIMID_WALK,			//歩きのアニメーション
};
//---------------------------------------------------------

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
void CEnemy::Init(VECTOR _pos)
{
	CCharacterBase::Init();
	m_attack.Init(ATTACK_SIZE,ATTACK_LENGTH, ATTACKABLE_RAD);
	m_FOV.Init(FOV_RADIUS);

	m_pos = _pos;
	m_rad = RADIUS;
	m_hp = MAX_HP;
	m_atk = ATK;
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
void CEnemy::Step(VECTOR _pos)
{
	//Activeがfalseなら処理をしない
	if (m_isActive == false)return;

	//攻撃の毎フレームする処理
	m_attack.Step();
	//視界範囲の毎フレームする処理
	m_FOV.Step();

	//移動処理
	Move(_pos);


	CCharacterBase::Step();

}

//-----------------------
//		描写処理
//-----------------------
void CEnemy::Draw()
{
	CCharacterBase::Draw();


#ifdef DEBUG
	
	//Activeがfalseなら描写しない
	if (m_isActive == false)return;

	DrawSphere3D(GetCenter(), m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG
	
}

//-----------------------
//		更新処理
//-----------------------
void CEnemy::Update()
{
	CCharacterBase::Update();

	//攻撃の更新
	m_attack.Update(GetCenter(), m_rot);
	//視界範囲の更新
	m_FOV.Update(m_pos);

}


//-----------------------
//		待機処理
//-----------------------
void CEnemy::Wait()
{
	//待機アニメーションを再生
	if (m_animData.m_id != ANIMID_WAIT)
	{
		Request(ANIMID_WAIT, 1.0f, true);
	}

	//動いていたら歩き状態に移行
	if (m_speed.x != 0.0f ||
		m_speed.z != 0.0f)
	{
		m_state = WALK;
	}

	//プレイヤーが攻撃可能距離にいた場合攻撃する
	if (m_attack.GetIsAttackable() == true)
	{
		//攻撃してない時に攻撃前に移行する
		if (m_attack.GetIsCoolDown() == true)
		{
			m_state = ATTACK_IN;
		}
	}

}

//-----------------------
//		歩く処理
//-----------------------
void CEnemy::Walk()
{
	//歩くアニメーション
	if (m_animData.m_id != ANIMID_WALK)
	{
		Request(ANIMID_WALK, 1.0f, true);
	}

	//止まっていたら待機状態に移行
	if (m_speed.x == 0.0f &&
		m_speed.z == 0.0f)
	{
		m_state = WAIT;
	}

	//プレイヤーが攻撃可能距離にいた場合攻撃する
	if (m_attack.GetIsAttackable() == true)
	{
		//攻撃してない時に攻撃前に移行する
		if (m_attack.GetIsCoolDown() == true)
		{
			m_state = ATTACK_IN;
		}
	}

}

//-----------------------
//		ジャンプ
//-----------------------
void CEnemy::Jump()
{

}

//-----------------------
//		攻撃前
//-----------------------
void CEnemy::AttackIn()
{

	//攻撃前のアニメーション
	if (m_animData.m_id != ANIMID_ATTACK_IN)
	{
		Request(ANIMID_ATTACK_IN, 1.0f);
	}

	//アニメーションが終わったら攻撃中に移行
	if (GetAnimEnd() == true)
	{
		m_state = ATTACK;
	}

}

//-----------------------
//		攻撃
//-----------------------
void CEnemy::Attack()
{
	//攻撃中のアニメーション
	if (m_animData.m_id != ANIMID_ATTACK)
	{
		Request(ANIMID_ATTACK, 1.0f, true);

		//攻撃の呼び出し
		m_attack.Request(GetCenter(), m_rot,
			ATTACK_TIME, ATTACK_COOL_TIME);
	}

	//攻撃が終わったら攻撃後に移動
	if (m_attack.GetActive() == false)
	{
		m_state = ATTACK_OUT;
	}

}

//-----------------------
//		攻撃後
//-----------------------
void CEnemy::AttackOut()
{

	//攻撃後のアニメーション
	if (m_animData.m_id != ANIMID_ATTACK_OUT)
	{
		Request(ANIMID_ATTACK_OUT, 1.0f);
	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = WAIT;
	}

}

//-----------------------
//		怯み
//-----------------------
void CEnemy::Stagger()
{
	//被弾のアニメーション
	if (m_animData.m_id != ANIMID_HIT)
	{
		Request(ANIMID_HIT, 1.0f);
	}

	//被弾のアニメーションが終わったら戻す
	if (GetAnimEnd() == true)
	{
		m_state = WAIT;
	}

}

//-----------------------
//		移動処理
//-----------------------
void CEnemy::Move(VECTOR _pos)
{
	//視界範囲内にプレイヤーが入っていないか、攻撃中と怯み中なら追わない
	if (m_FOV.GetHit() == false ||
		m_attack.GetActive() == true ||
		m_state == STAGGER)return;

	//敵がプレイヤーの方向を向く
	m_rot.y = static_cast<float>(atan2(static_cast<float>(m_pos.x -_pos.x), static_cast<float>(m_pos.z - _pos.z)));

	//プレイヤーが攻撃可能範囲にいる場合移動しない
	if (m_attack.GetIsAttackable() == true)return;

	//プレイヤーが目の前にいる時に進む速度
	VECTOR defaultDir = { 0.0f,0.0f,-MOVE_SPEED };
	//上記を行列に変換
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(m_rot.y);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

}

