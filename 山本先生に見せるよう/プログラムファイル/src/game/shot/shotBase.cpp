#include "shotBase.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"
#include "../../lib/effekseer/effekseer.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
constexpr float MOVE_SPEED = 0.5f;			//スピード
constexpr float HOMING_LEN = 45.0f;			//ホーミングする距離
//----------------------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CShotBase::CShotBase()
{
	Init();
}

//-----------------------
//	デストラクタ
//-----------------------
CShotBase::~CShotBase()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CShotBase::Init()
{
	CObject::Init();
	m_lostTime = 0;
	m_timeCount = 0;
	m_atk = 0;
	m_rad = 0.0f;
	m_moveSpeed = 0.0f;
	m_effectHndl = -1;
	m_objectName = OBJECT_SHOT;
	m_isHoming = true;
	m_isPushed = false;
}

//-----------------------
//	モデルロード
//-----------------------
void CShotBase::Load(int _modelHndl)
{
	CObject::DuplicateModel(_modelHndl);
}

//-----------------------
//毎フレームする処理
//-----------------------
void CShotBase::Step()
{

	CObject::Step();

	//Activeがfalseなら処理をしない
	if (m_isActive == false)
	{
		m_targetPos = nullptr;
		m_isHoming = true;
		return;
	}

	if (m_targetPos != nullptr)
	{
		VECTOR vLen = VSub(m_pos, *m_targetPos);
		float fLen = VSize(vLen);

		if (fLen >= HOMING_LEN && m_isHoming == true)
		{
			m_rot.y = atan2f(m_pos.x - m_targetPos->x, m_pos.z - m_targetPos->z);

			if (m_pos.y > m_targetPos->y)
			{
				m_speed.y -= 1.0f;
			}
			else if (m_pos.y < m_targetPos->y)
			{
				m_speed.y += 1.0f;
			}

		}
		else
		{
			m_isHoming = false;
		}

	}

	//移動処理
	Move();

	m_timeCount++;
	//タイムカウントが消える時間を過ぎたら消える
	if (m_timeCount >= m_lostTime)
	{
		m_isActive = false;
	}

}

//-----------------------
//		描写処理
//-----------------------
void CShotBase::Draw()
{
	CObject::Draw();	
}

//-----------------------
//		更新処理
//-----------------------
void CShotBase::Update()
{
	CObject::Update();

	//エフェクトハンドルがある時だけ
	if (m_effectHndl != -1)
	{
		//エフェクトの座標を動かす
		CEffekseerCtrl::SetPosition(m_effectHndl, m_pos);
	}

}

//-----------------------
//		終了処理
//-----------------------
void CShotBase::Exit()
{
	CObject::Exit();
	if (m_effectHndl != -1)
	{
		CEffekseerCtrl::Stop(m_effectHndl);
		m_effectHndl = -1;
	}
}

//-----------------------
//		呼び出し
//-----------------------
void CShotBase::Request(VECTOR _pos, VECTOR _rot, float _rad, float _speed, int _atk, int _lostTime,
	tagPlayerName _name,int _effectHndl, VECTOR* _targetPos)
{
	//弾の設定
	m_pos = _pos;
	m_rot = _rot;
	m_rad = _rad;
	m_moveSpeed = _speed;
	m_atk = _atk;
	m_lostTime = _lostTime;
	m_effectHndl = _effectHndl;
	m_shotName = _name;
	m_targetPos = _targetPos;

	m_pos.y -= m_rad * 0.5f;

	m_scale = { _rad/2.2f ,_rad/2.2f,_rad/2.2f };

	m_isActive = true;
}

//-----------------------
//		移動処理
//-----------------------
void CShotBase::Move()
{
	if (m_isActive == false)return;

	//プレイヤーが目の前にいる時に進む速度
	VECTOR defaultDir = { 0.0f,0.0f,-m_moveSpeed};

	//上記を行列に変換
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(m_rot.y);
	//X軸回転行列
	MATRIX mRotX = CMyMath::GetPitchMatrix(m_rot.x);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	//m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

}

