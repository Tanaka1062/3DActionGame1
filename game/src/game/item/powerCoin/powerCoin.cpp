#include "powerCoin.h"
#include "../../lib/myMath/myMath.h"

static const float DROP_SPEED = 14.0f;			//飛ぶスピード
static const float DROP_JUMP = 7.0f;			//上に飛ぶ力

CPowerCoin::CPowerCoin()
{
	m_state = POWER_COIN_WAIT;
	m_playerName = PLAYER_NONE;
}

CPowerCoin::~CPowerCoin()
{
	
}

//---------------------
//		 初期化
//---------------------
void CPowerCoin::Init(CPlayer* _player)
{
	CItemBase::Init(_player);

	m_state = POWER_COIN_WAIT;
	m_playerName = PLAYER_NONE;

	m_isActive = false;

}

//---------------------
// 毎フレームする処理
//---------------------
void CPowerCoin::Step()
{
	CItemBase::Step();
}

//---------------------
//		数値の更新
//---------------------
void CPowerCoin::Update()
{
	CItemBase::Update();

	//コインを飛ばす
	if (m_state == POWER_COIN_FLYING)
	{
		m_speed.x *= 0.9f;
		m_speed.z *= 0.9f;

		VECTOR speed = m_speed;

		speed.y = 0.0f;

		float speedLen = VSize(speed);

		if (speedLen <= 0.1f)
		{
			m_speed.x = 0.0f;
			m_speed.z = 0.0f;
			m_state = POWER_COIN_WAIT;
		}
	}
}

//---------------------
//	当たった時の処理
//---------------------
void CPowerCoin::HitCalc(tagPlayerName _name)
{
	m_isActive = false;
	m_playerName = _name;
}

//---------------------
//	コインのドロップ
//---------------------
void CPowerCoin::Drop(VECTOR _pos, float _rotY)
{
	//角度ゼロで進む速度
	VECTOR defaultDir = { 0.0f,DROP_JUMP,DROP_SPEED };
	//上記を行列に変換する
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(_rotY);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

	m_pos = _pos;
	m_state = POWER_COIN_FLYING;
	m_isActive = true;
	m_playerName = PLAYER_NONE;
}

//---------------------
//	   コインの消失
//---------------------
void CPowerCoin::Delete()
{
	m_state = POWER_COIN_WAIT;
	m_playerName = PLAYER_NONE;
}

