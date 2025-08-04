#include "shot.h"
#include <math.h>
#include "../common.h"

//定義関連==================================
static const float MOVE_SPEED = 1.0f;				//弾の速度
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const float ACTIVE_LENGTH = 500.0f;			//弾の生存範囲
//==========================================

//---------------------------
//		コンストラクタ
//---------------------------
CShot::CShot()
{
	CObject::Init();
	Init();
}

//---------------------------
//		デストラクタ
//---------------------------
CShot::~CShot()
{
	Exit();
}

//---------------------------
//		初期化
//---------------------------
void CShot::Init()
{
	m_pos = ZERO;
	m_speed = ZERO;
	m_hndl = -1;
	m_radius = 2.0f;
	m_isActive = false;
}


//---------------------------
//		毎フレームする処理
//---------------------------
void CShot::Step()
{
	//呼び出されていない場合は終了
	if (!m_isActive)return;
	//プレイヤーの移動処理
	Move();

	//範囲外に出たら弾を削除
	if (m_pos.x < -ACTIVE_LENGTH || m_pos.x > ACTIVE_LENGTH ||
		m_pos.z < -ACTIVE_LENGTH || m_pos.z > ACTIVE_LENGTH)
	{
		m_isActive = false;
	}

}

//---------------------------
//		描写
//---------------------------
void CShot::Draw()
{
	if (m_isActive)
	{
		MV1DrawModel(m_hndl);


#ifdef DEBUG
		//当たり判定を目視できるように
		DrawSphere3D(m_pos, m_radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
#endif // DEBUG



	}
}


//---------------------------
//		移動
//---------------------------
void CShot::Move()
{
	//現在の座標に速度を加算する
	m_pos = VAdd(m_pos, m_speed);


}

//---------------------------
//		弾をリクエスト
//---------------------------
bool CShot::Request(const VECTOR& _pos, const VECTOR& _speed)
{
	//既に弾が発射されていたら失敗
	if (m_isActive)return false;

	//必要な状況を渡してく
	m_isActive = true;
	m_pos = _pos;
	m_speed = _speed;

	return true;
}

//---------------------------
//		当たり判定後の処理
//---------------------------
void CShot::HitCalc()
{
	m_isActive = false;
}
