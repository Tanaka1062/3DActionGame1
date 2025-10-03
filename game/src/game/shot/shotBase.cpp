#include "shotBase.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"
#include "../../lib/effekseer/effekseer.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const float MOVE_SPEED = 0.5f;			//スピード
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
	CActor::Init();
	m_lostTime = 0;
	m_timeCount = 0;
	m_atk = 0;
	m_rad = 0.0f;
	m_moveSpeed = 0.0f;
	m_effectHndl = -1;
}

//-----------------------
//	モデルロード
//-----------------------
void CShotBase::Load(int _modelHndl)
{
	CActor::DuplicateModel(_modelHndl);
}

//-----------------------
//毎フレームする処理
//-----------------------
void CShotBase::Step()
{

	//Activeがfalseなら処理をしない
	if (m_isActive == false)return;

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
	CActor::Draw();


#ifdef DEBUG
	
	//Activeがfalseなら描写しない
	if (m_isActive == false)return;

	DrawSphere3D(m_pos, m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG
	
}

//-----------------------
//		更新処理
//-----------------------
void CShotBase::Update()
{
	CActor::Update();

	//エフェクトハンドルがある時だけ
	if (m_effectHndl != -1)
	{
		//エフェクトの座標を動かす
		CEffekseerCtrl::SetPosition(m_effectHndl, GetCenter());
	}

}

//-----------------------
//		終了処理
//-----------------------
void CShotBase::Exit()
{
	CActor::Exit();
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
	int _effectHndl)
{
	//弾の設定
	m_pos = _pos;
	m_rot = _rot;
	m_rad = _rad;
	m_moveSpeed = _speed;
	m_atk = _atk;
	m_lostTime = _lostTime;
	m_effectHndl = _effectHndl;

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
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

}

