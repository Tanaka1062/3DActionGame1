#include "enemy.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
{ "data/model/enemy/enemyTest.mv1" };				//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,0.0f,0.0f };	//初期座標
static const int MAX_HP = 100;						//体力
static const int ATK = 5;							//攻撃力
static const float MOVE_SPEED = 0.75f;				//移動スピード
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
	ANIMID_DIE,				//死亡時のアニメーション
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
void CEnemy::Init(CAttackManager* _attackManager)
{
	CCharacterBase::Init(_attackManager);
	m_attack.Init(ATTACK_SIZE,ATTACK_LENGTH, ATTACKABLE_RAD);
	m_FOV.Init(FOV_RADIUS);

	m_rootHndl = -1;
	m_rootId = 0;
	m_pos = INIT_POS;
	m_rad = RADIUS;
	m_hp = MAX_HP;
	m_atk = ATK;
}

//-----------------------
//		待機処理
//-----------------------
void CEnemy::Wait()
{
	//待機アニメーションを再生
	if (m_animData.m_id != ANIMID_WAIT)
	{
		RequestAnim(ANIMID_WAIT, 1.0f, true);
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
		RequestAnim(ANIMID_WALK, 1.0f, true);
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
		RequestAnim(ANIMID_ATTACK_IN, 0.40f);
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
		RequestAnim(ANIMID_ATTACK, 1.0f, true);

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
		RequestAnim(ANIMID_ATTACK_OUT, 1.0f);
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
		RequestAnim(ANIMID_HIT, 1.0f);
	}

	//ノックバック
	KnockBack();

}

//-----------------------
//		死亡
//-----------------------
void CEnemy::Die()
{
	//死亡のアニメーション
	if (m_animData.m_id != ANIMID_DIE)
	{
		RequestAnim(ANIMID_DIE, 0.5f);
	}

	//死亡アニメーションが終わったら消える
	if (GetAnimEnd() == true)
	{
		m_isActive = false;
	}

}

//-----------------------
//	追いかける移動処理
//-----------------------
void CEnemy::MoveChase(VECTOR _pos)
{

	//待機状態と移動状態以外は移動を出来ないようにする
	switch (m_state)
	{
	case WAIT:
	case WALK:
		break;
	default:
		return;
	}

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

//-----------------------
//	 ルートを移動処理
//-----------------------
void CEnemy::MoveRoot()
{
	//待機状態と移動状態以外は移動を出来ないようにする
	switch (m_state)
	{
	case WAIT:
	case WALK:
		break;
	default:
		return;
	}

	//次の目的地の座標取得
	VECTOR targetPos = MV1GetFramePosition(m_rootHndl,m_root[m_rootId]);
	//高さは無視する
	targetPos.y = m_pos.y;
	//目的地に向けてのベクトルを計算
	VECTOR dir = VSub(targetPos, m_pos);
	//目的地までの距離を取得
	float len = VSize(dir);

	//目的地までの距離が一定範囲内
	if (len <= 1.5f)
	{
		//目的地に一気に移動
		m_pos = targetPos;
		//ルートを次の目的地に変更
		m_rootId = (m_rootId + 1) % m_root.size();
	}
	//目的地まで、まだ距離がある
	else
	{
		//高さは無視して正規化
		dir.y = 0.0f;
		dir = VNorm(dir);
		//移動速度分の長さに変更
		dir = VScale(dir, MOVE_SPEED);
		//現在の速度に加算
		m_speed = VAdd(m_speed, dir);
	}

	//進行方向を向かせる
	m_rot.y = atan2f(-dir.x, -dir.z);
}

