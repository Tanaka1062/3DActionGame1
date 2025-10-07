#include "enemyBase.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const VECTOR INIT_POS = { 0.0f,0.0f,0.0f };	//初期座標
//----------------------------------------------

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
CEnemyBase::CEnemyBase()
{
	Init();
}

//-----------------------
//	デストラクタ
//-----------------------
CEnemyBase::~CEnemyBase()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CEnemyBase::Init()
{
	CCharacterBase::Init();
	m_attack.Init();
	m_FOV.Init(0.0f);

	m_moveSpeed = 0.0f;
	m_rootHndl = -1;
	m_rootId = 0;
	m_pos = INIT_POS;
	m_rad = 0.0f;
	m_hp = 0;
	m_atk = 0;
}

//-----------------------
//	モデルロード
//-----------------------
void CEnemyBase::Load(int _rootHndl, int _modelHndl)
{
	CActor::DuplicateModel(_modelHndl);

	if (m_rootHndl == -1)
	{
		m_rootHndl = _rootHndl;
	}

	//ルート移動の初期化設定------------------
	//最初の位置を取得し、そこに配置する
	VECTOR start = MV1GetFramePosition(m_rootHndl, m_root[m_rootId]);
	m_pos = start;
	//視界も最初の位置を設定
	m_FOV.SetPos(start);

	//ルートを次の位置に変更
	m_rootId++;
	//----------------------------------------

}

//-----------------------
//毎フレームする処理
//-----------------------
void CEnemyBase::Step(VECTOR _pos)
{
	//Activeがfalseなら処理をしない
	if (m_isActive == false)return;

	//攻撃の毎フレームする処理
	m_attack.Step();
	//視界範囲の毎フレームする処理
	m_FOV.Step();

	//視界にプレイヤーが入ってなかったら追わない
	if (m_FOV.GetHit() == false)
	{
		//ルート移動処理
		MoveRoot();
	}
	else
	{
		//追いかける移動処理
		MoveChase(_pos);
	}

	CCharacterBase::Step();

}

//-----------------------
//		描写処理
//-----------------------
void CEnemyBase::Draw()
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
void CEnemyBase::Update()
{
	CCharacterBase::Update();

	//怯み状態以外はスピードをリセット
	if (m_state != STAGGER)
	{
		//速度のリセット
		ResetSpeed();
	}

	//攻撃の更新
	m_attack.Update(GetCenter(), m_rot);
	//視界範囲の更新
	m_FOV.Update(m_pos);

}

//-----------------------
//	   ルートを設定
//-----------------------
void CEnemyBase::SetRoot(int _root)
{
	m_root.push_back(_root);
}

//-----------------------
//		待機処理
//-----------------------
void CEnemyBase::Wait()
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
void CEnemyBase::Walk()
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
void CEnemyBase::Jump()
{

}

//-----------------------
//		攻撃前
//-----------------------
void CEnemyBase::AttackIn()
{

}

//-----------------------
//		攻撃
//-----------------------
void CEnemyBase::Attack()
{
}

//-----------------------
//		攻撃後
//-----------------------
void CEnemyBase::AttackOut()
{
}

//-----------------------
//		怯み
//-----------------------
void CEnemyBase::Stagger()
{
	//被弾のアニメーション
	if (m_animData.m_id != ANIMID_HIT)
	{
		Request(ANIMID_HIT, 1.0f);
	}

	//ノックバック
	MoveBack();

}

//-----------------------
//		死亡
//-----------------------
void CEnemyBase::Die()
{
	//死亡のアニメーション
	if (m_animData.m_id != ANIMID_DIE)
	{
		Request(ANIMID_DIE, 0.5f);
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
void CEnemyBase::MoveChase(VECTOR _pos)
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
	m_rot.y = static_cast<float>(atan2(static_cast<float>(m_pos.x - _pos.x), static_cast<float>(m_pos.z - _pos.z)));

	//プレイヤーが攻撃可能範囲にいる場合移動しない
	if (m_attack.GetIsAttackable() == true)return;

	//プレイヤーが目の前にいる時に進む速度
	VECTOR defaultDir = { 0.0f,0.0f,-m_moveSpeed };
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
void CEnemyBase::MoveRoot()
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
	VECTOR targetPos = MV1GetFramePosition(m_rootHndl, m_root[m_rootId]);
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
		dir = VScale(dir, m_moveSpeed);
		//現在の速度に加算
		m_speed = VAdd(m_speed, dir);
	}

	//進行方向を向かせる
	m_rot.y = atan2f(-dir.x, -dir.z);
}

