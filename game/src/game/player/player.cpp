#include "player.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"
#include "../../lib/input/controllerInput.h"
#include"../../lib/input/keyInput.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
{ "data/model/player/playerTest.mv1" };				//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,1.0f,0.0f };	//初期座標
static const int MAX_HP = 100;						//体力
static const int ATK = 400;							//攻撃力
static const float MOVE_SPEED = 0.5f;				//移動スピード
static const float RADIUS = 2.5f;					//半径
//----------------------------------------------

//攻撃関連---------------------------
static const float ATTACK_SIZE = 3.0f;				//攻撃範囲
static const float ATTACK_LENGTH = 5.0f;			//攻撃の長さ
static const int ATTACK_TIME = 10;					//攻撃の判定の時間(フレーム)
static const int ATTACK_COOL_TIME = 30;				//攻撃のクールタイム(フレーム)
//-----------------------------------

//アイテム関連--------------------------------
static const int SHOT_ATK = 400;					//弾の攻撃力
static const float SHOT_MOVE_SPEED = 1.0f;			//弾の移動スピード
static const int SHOT_LOST_TIME = 240;				//弾の消えるまでのスピード
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
CPlayer::CPlayer()
{
	CCharacterBase::Init();

	m_isPickUpItem = false;
	m_item = nullptr;
}

//-----------------------
//	デストラクタ
//-----------------------
CPlayer::~CPlayer()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CPlayer::Init(CShotManager* _shot)
{
	CCharacterBase::Init(_shot);
	m_attack.Init(ATTACK_SIZE,ATTACK_LENGTH);

	m_pos = INIT_POS;
	m_rad = RADIUS;
	m_hp = MAX_HP;
	m_atk = ATK;

}

//-----------------------
//	モデルロード
//-----------------------
void CPlayer::Load()
{
	CActor::LoadModel(MODEL_PATH);
}

//-----------------------
//毎フレームする処理
//-----------------------
void CPlayer::Step(float _rotY)
{
	//攻撃の毎フレームする処理
	m_attack.Step();

	//移動処理
	Move(_rotY);

	//アイテム使用処理
	Item();


	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_speed.y += 10.0f;
	}

	CCharacterBase::Step();
}

//-----------------------
//		描写処理
//-----------------------
void CPlayer::Draw()
{
	CCharacterBase::Draw();

#ifdef DEBUG
	//当たり判定を表示
	DrawSphere3D(GetCenter(), m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
#endif // DEBUG
	//体力を表示
	DrawFormatString(32, 32, GetColor(255, 0, 0), "hp:%d", m_hp);

}

//-----------------------
//		更新処理
//-----------------------
void CPlayer::Update()
{
	CCharacterBase::Update();

	//攻撃の更新
	m_attack.Update(GetCenter(), m_rot);

	//アイテムを取ろうとしているかを初期化
	m_isPickUpItem = false;

}

//-----------------------
//アイテムを取るかを取得
//-----------------------
bool CPlayer::GetItem()
{
	//フラグ保存用
	bool flg = m_isPickUpItem;

	//アイテムを取ろうとしているかを初期化
	m_isPickUpItem = false;

	return flg;
}


//-----------------------
//		待機処理
//-----------------------
void CPlayer::Wait()
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
	
	//攻撃の呼び出し
	RequestAttack();
}

//-----------------------
//		歩く処理
//-----------------------
void CPlayer::Walk()
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

	//攻撃の呼び出し
	RequestAttack();

}

//-----------------------
//		ジャンプ
//-----------------------
void CPlayer::Jump()
{

}

//-----------------------
//		攻撃前
//-----------------------
void CPlayer::AttackIn()
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
//		攻撃中
//-----------------------
void CPlayer::Attack()
{

	//攻撃中のアニメーション
	if (m_animData.m_id != ANIMID_ATTACK)
	{
		Request(ANIMID_ATTACK, 1.0f,true);

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
void CPlayer::AttackOut()
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
//	  アイテム使用前
//-----------------------
void CPlayer::ItemUseIn()
{
	//アイテム使用前のアニメーション
	if (m_animData.m_id != ANIMID_ITEM_USE_IN)
	{
		Request(ANIMID_ITEM_USE_IN, 1.0f);
	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = ITEM_USE;
	}

}

//-----------------------
//	 アイテム使用中
//-----------------------
void CPlayer::ItemUse()
{
	//アイテム使用中のアニメーション
	if (m_animData.m_id != ANIMID_ITEM_USE)
	{
		Request(ANIMID_ITEM_USE, 1.0f);

		//アイテムを使用する
		m_item->Use();
	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = ITEM_USE_OUT;
	}

}

//-----------------------
//	 アイテム使用後
//-----------------------
void CPlayer::ItemUseOut()
{
	//アイテム使用後のアニメーション
	if (m_animData.m_id != ANIMID_ITEM_USE_OUT)
	{
		Request(ANIMID_ITEM_USE_OUT, 1.0f);
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
void CPlayer::Stagger()
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
//		死亡
//-----------------------
void CPlayer::Die()
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
//		移動処理
//-----------------------
void CPlayer::Move(float _rotY)
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

	//コントローラーを使っているか
	bool isController = false;

	if (CControllerInput::GetLY() != 0 ||
		CControllerInput::GetLX() != 0)
	{
		isController = true;
	}

	//移動ベクトル
	VECTOR speed = { 0.0f,0.0f,0.0f };
	speed.z = 0.0f;
	//コントローラー用前進後退
	if (isController == true)
	{
		speed.z = MOVE_SPEED * CControllerInput::GetLY();
	}
	//キーボード用前進
	else if (CheckHitKey(KEY_INPUT_W) != 0)
	{
		speed.z = -MOVE_SPEED;
	}
	//キーボード用後退
	else if (CheckHitKey(KEY_INPUT_S) != 0)
	{
		speed.z = MOVE_SPEED;
	}

	//左右にどれだけ移動するか
	speed.x = 0.0f;
	//コントローラー用左右移動
	if (isController == true)
	{
		speed.x = -MOVE_SPEED * CControllerInput::GetLX();
	}
	//キーボード用左移動
	else if (CheckHitKey(KEY_INPUT_A) != 0)
	{
		speed.x = MOVE_SPEED;
	}
	//キーボード用右移動
	else if (CheckHitKey(KEY_INPUT_D) != 0)
	{
		speed.x = -MOVE_SPEED;
	}

	//カメラの角度がオールゼロの時に進む速度
	VECTOR defaultDir = { speed.x,0.0f,speed.z };
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

	//移動方向を向く
	if (m_speed.x != 0 || m_speed.z != 0)
		m_rot.y = atan2f(-m_speed.x,-m_speed.z);

}

//-----------------------
//攻撃を呼び出す処理
//-----------------------
void CPlayer::RequestAttack()
{
	//攻撃ボタンを押したか
	if (CheckHitKey(KEY_INPUT_J) != 0 ||
		CControllerInput::IsTrg(BUTTON_X))
	{

		//攻撃してない時に攻撃前に移行する
		if (m_attack.GetIsCoolDown() == true)
		{
			m_state = ATTACK_IN;
		}
	}
}

//-----------------------
//	   アイテム処理
//-----------------------
void CPlayer::Item()
{
	//アイテムが何もなかったら処理をしない
	if (m_item == nullptr)return;

	//待機状態と歩いてる状態以外は処理をしない
	switch (m_state)
	{
	case WAIT:
	case WALK:
		break;
	default:
		return;
	}

	//ボタンを押されたらアイテム使用前状態に移行
	if (CheckHitKey(KEY_INPUT_K) != 0 ||
		CControllerInput::IsTrg(BUTTON_A) == true)
	{
		m_state = ITEM_USE_IN;
	}

}

//-----------------------
//	   アイテムを拾う
//-----------------------
void CPlayer::PickUpItem()
{
	if (CheckHitKey(KEY_INPUT_I) != 0 ||
		CControllerInput::IsTrg(BUTTON_B) == true)
	{
		m_isPickUpItem = true;
	}
}

