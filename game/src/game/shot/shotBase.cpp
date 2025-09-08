#include "shotBase.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
{ "data/model/shot/shotTest.mv1" };				//ロードするファイル名
static const float RADIUS = 2.5f;				//半径
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
	CShotBase::Init();

	m_rad = RADIUS;
}

//-----------------------
//	モデルロード
//-----------------------
void CShotBase::Load(const char* _filePath)
{
	CActor::LoadModel(_filePath);
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

	CShotBase::Step();

}

//-----------------------
//		描写処理
//-----------------------
void CShotBase::Draw()
{
	CShotBase::Draw();


#ifdef DEBUG
	
	//Activeがfalseなら描写しない
	if (m_isActive == false)return;

	DrawSphere3D(GetCenter(), m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

#endif // DEBUG
	
}

//-----------------------
//		更新処理
//-----------------------
void CShotBase::Update()
{
	CShotBase::Update();
}

//-----------------------
//		呼び出し
//-----------------------
void CShotBase::Request(VECTOR _pos, VECTOR _rot, VECTOR _speed, int _atk, int _lostTime)
{
	//弾の設定
	m_pos = _pos;
	m_rot = _rot;
	m_speed = _speed;
	m_atk = _atk;
	m_lostTime = _lostTime;

	m_isActive = true;
}

//-----------------------
//		移動処理
//-----------------------
void CShotBase::Move()
{
	if (m_isActive == false)return;

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

