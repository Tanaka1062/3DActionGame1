#include "powerUpGouge.h"

constexpr int POWER_GOUGE_LEN = 495;		//パワーゲージの長さ		

//コンストラクタ・デストラクタ
CPowerUpGouge::CPowerUpGouge()
{
	Init();
}

CPowerUpGouge::~CPowerUpGouge()
{
	Exit();
}

//初期化
void CPowerUpGouge::Init(VECTOR _pos, float _rot)
{
	m_powerUpGouge = 0.0f;
	m_powerUp = 0.0f;
	m_player = nullptr;
	C2DUi::Init(_pos, _rot);

}

//毎フレームする処理
void CPowerUpGouge::Step()
{
	//パワーゲージを１００で割る
	m_powerUpGouge = static_cast<float>(0.01f * POWER_GOUGE_LEN);

	//パワーゲージの割合をもとめる
	m_powerUp = static_cast<float>(m_player->GetTransformTimeCount()) / static_cast<float>(TRANSFORM_TIME);

	//パワーゲージを求める
	m_powerUp = m_powerUp * m_powerUpGouge * 100.0f;

}

//描写
void CPowerUpGouge::Draw(float _size)
{

	if (m_player == nullptr)return;


}


