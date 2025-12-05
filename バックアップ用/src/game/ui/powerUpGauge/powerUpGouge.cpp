#include "powerUpGouge.h"

static const int POWER_GOUGE_LEN = 495;		//パワーゲージの長さ		

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

	if (m_player->GetIsTransform() == false)return;

	C2DUi::Draw(_size);

	switch (m_player->GetPlayerName())
	{
	case PLAYER_1:
		DrawBox(static_cast<int>(m_pos.x + (POWER_GOUGE_LEN * 0.5f)), static_cast<int>(m_pos.y + 10),
			static_cast<int>((m_pos.x + (POWER_GOUGE_LEN * 0.5f)) - m_powerUp), static_cast<int>(m_pos.y - 10), GetColor(255, 165, 0), TRUE);
		break;
	case PLAYER_2:
		DrawBox(static_cast<int>(m_pos.x - (POWER_GOUGE_LEN * 0.5f)), static_cast<int>(m_pos.y + 10),
			static_cast<int>((m_pos.x - (POWER_GOUGE_LEN * 0.5f)) + m_powerUp), static_cast<int>(m_pos.y - 10), GetColor(255, 165, 0), TRUE);
		break;
	}



}


