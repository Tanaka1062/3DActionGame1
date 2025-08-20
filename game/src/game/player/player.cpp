#include "player.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"
#include "../../lib/input/controllerInput.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
{ "data/model/player/playerTest.mv1" };				//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,1.0f,0.0f };	//初期座標
static const int MAX_HP = 100;						//体力
static const int ATTACK = 10;						//攻撃力
static const float MOVE_SPEED = 0.5f;				//移動スピード
static const float RADIUS = 2.5f;					//半径
//----------------------------------------------

//攻撃関連---------------------------
static const float ATTACK_SIZE = 3.0f;				//攻撃範囲
static const float ATTACK_LENGTH = 2.0f;			//攻撃の長さ
static const int ATTACK_TIME = 120;					//攻撃の判定の時間(フレーム)

//-----------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CPlayer::CPlayer()
{
	Init();
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
void CPlayer::Init()
{
	CCharacterBase::Init();
	m_attack.Init();

	m_pos = INIT_POS;
	m_rad = RADIUS;
	m_hp = MAX_HP;
	m_atk = ATTACK;
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
	CCharacterBase::Step();
	//攻撃の毎フレームする処理
	m_attack.Step();

	//移動処理
	Move(_rotY);

	//攻撃処理
	if (CheckHitKey(KEY_INPUT_J) != 0 &&
		m_attack.GetActive() == false)
	{
		m_attack.Request(m_pos,m_rot, ATTACK_SIZE, ATTACK_LENGTH, ATTACK_TIME);
	}

	//攻撃の更新
	m_attack.Update(m_pos, m_rot);

}

//-----------------------
//		描写処理
//-----------------------
void CPlayer::Draw()
{
	CCharacterBase::Draw();

#ifdef DEBUG

	DrawSphere3D(GetCenter(), m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG
	
}

//-----------------------
//		待機処理
//-----------------------
void CPlayer::Wait()
{

}

//-----------------------
//		歩く処理
//-----------------------
void CPlayer::Walk()
{

}

//-----------------------
//		ジャンプ
//-----------------------
void CPlayer::Jump()
{

}

//-----------------------
//		攻撃
//-----------------------
void CPlayer::Attack()
{

}

//-----------------------
//		怯み
//-----------------------
void CPlayer::Stagger()
{

}

//-----------------------
//		移動処理
//-----------------------
void CPlayer::Move(float _rotY)
{

	//コントローラーを使っているか
	bool isController = false;

	if (CControllerInput::GetLY() != 0 ||
		CControllerInput::GetLX() != 0)
	{
		isController = true;
	}

	//前後にどれだけ移動するか
	float speedZ = 0.0f;
	//コントローラー用前進後退
	if (isController == true)
	{
		speedZ = MOVE_SPEED * CControllerInput::GetLY();
	}
	//キーボード用前進
	else if (CheckHitKey(KEY_INPUT_W) != 0)
	{
		speedZ = -MOVE_SPEED;
	}
	//キーボード用後退
	else if (CheckHitKey(KEY_INPUT_S) != 0)
	{
		speedZ = MOVE_SPEED;
	}

	//左右にどれだけ移動するか
	float speedX = 0.0f;
	//コントローラー用左右移動
	if (isController == true)
	{
		speedX = -MOVE_SPEED * CControllerInput::GetLX();
	}
	//キーボード用左移動
	else if (CheckHitKey(KEY_INPUT_A) != 0)
	{
		speedX = MOVE_SPEED;
	}
	//キーボード用右移動
	else if (CheckHitKey(KEY_INPUT_D) != 0)
	{
		speedX = -MOVE_SPEED;
	}

	//カメラの角度がオールゼロの時に進む速度
	VECTOR defaultDir = { speedX,0.0f,speedZ };
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
		m_rot.y = static_cast<float>(atan2(static_cast<float>(-m_speed.x), static_cast<float>(-m_speed.z)));

}

