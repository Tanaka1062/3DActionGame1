#include "player.h"
#include <math.h>
#include"../../lib/input.h"
#include "../common.h"
#include"../system/soundManager.h"

//定義関連==================================
static const float MOVE_SPEED = 1.0f;								//プレイヤーの速度
static const float MOVE_LENGTH = 75.0f;								//移動範囲の長さ
static const float ROTATE_SPEED = 0.025f;							//回転速度
static const float SHOT_SPEED = 2.0f;								//弾の速度
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };						//VECTOR用初期化
static const VECTOR ROTINIT = { 0.0f,180 * (DX_PI_F / 180),0.0f };	//プレイヤーの初期回転角度
static const float RADIUS = 10.0f;									//半径
//==========================================

//---------------------------
//	コンストラクタ
//---------------------------
CPlayer::CPlayer()
{
	CObject::Init();
	Init();
}

//---------------------------
//	デストラクタ
//---------------------------
CPlayer::~CPlayer()
{
	Exit();
}

//---------------------------
//	初期化
//---------------------------
void CPlayer::Init()
{
	m_pos = ZERO;
	m_rot = ROTINIT;
	m_speed = ZERO;
	m_hndl = -1;
	m_radius = RADIUS;
	m_isActive = true;
}

//---------------------------
//	毎フレームする処理
//---------------------------
void CPlayer::Step(CShotManager& _shot)
{
	if (m_isActive == false)return;

	//プレイヤーの移動処理
	Move();
	//プレイヤーの回転
	//Rotate();
	//弾の発射
	Shot(_shot);

}

//---------------------------
//			描写
//---------------------------
void CPlayer::Draw()
{
	if (m_isActive == false)return;

	CObject::Draw();

#ifdef DEBUG

	//当たり判定を目視できるように
	DrawSphere3D(m_pos, m_radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG

}

//---------------------------
//	当たり判定の座標用
//---------------------------
VECTOR CPlayer::GetCenter()
{
	VECTOR res = m_pos;
	res.y += m_radius;

	return res;
}

//---------------------------
//	当たり判定後の処理
//---------------------------
void CPlayer::HitCalc()
{
	m_isActive = false;
}


//---------------------------
//		移動
//---------------------------
void CPlayer::Move()
{
	
	float speed = 0.0f;		//実際の速度

	//左に移動
	if (CInput::IsInputRep(KEY_LEFT) == true)
	{
		speed = -MOVE_SPEED;
	}
	//右に移動
	if (CInput::IsInputRep(KEY_RIGHT) == true)
	{
		speed = MOVE_SPEED;
	}

	m_speed.x = speed;

	//速度を座標に足し算する
	m_pos = VAdd(m_pos, m_speed);

	//移動範囲を制限する
	if (m_pos.x <= -MOVE_LENGTH + RADIUS)
	{
		m_pos.x = -MOVE_LENGTH + RADIUS;
	}
	if (m_pos.x >= MOVE_LENGTH - RADIUS)
	{
		m_pos.x = MOVE_LENGTH - RADIUS;
	}

}

//---------------------------
//		回転
//---------------------------
void CPlayer::Rotate()
{
	if (CInput::IsInputRep(KEY_LEFT) == true)
	{
		m_rot.y -= ROTATE_SPEED;
	}
	if (CInput::IsInputRep(KEY_RIGHT) == true)
	{
		m_rot.y += ROTATE_SPEED;
	}
}

//---------------------------
//			弾を発射
//---------------------------
void CPlayer::Shot(CShotManager& _shot)
{
	//弾を発射する
	if (CInput::IsInputTrg(KEY_SHOT) == true)
	{
		CSoundManager::Play(CSoundManager::SE_PLSHOT);

		VECTOR speed;
		//速度計算を三角関数で計算する
		speed.x = sinf(m_rot.y) * -SHOT_SPEED;
		speed.y = 0.0f;
		speed.z = cosf(m_rot.y) * -SHOT_SPEED;

		_shot.RequestPlayerShot(GetCenter(), speed);
	}

}


