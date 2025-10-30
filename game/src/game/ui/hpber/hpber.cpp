#include "hpber.h"

static const int HP_BAR_LEN = 100;		//HPバーの長さ		

//コンストラクタ・デストラクタ
CHpber::CHpber()
{
	Init();
}

CHpber::~CHpber()
{
	Exit();
}

//初期化
void CHpber::Init(VECTOR _pos, float _rot)
{
	m_player = nullptr;
	C2DUi::Init(_pos, _rot);

}

//毎フレームする処理
void CHpber::Step()
{
	
}

//描写
void CHpber::Draw(float _size)
{
	C2DUi::Draw(_size);

	float hpbar = m_player->GetHp() * HP_BAR_LEN;
	float hp = hpbar / m_player->GetHpMax();

	DrawBox(m_pos.x - 30, m_pos.y - 30,
		(m_pos.x - 30) + hp, m_pos.y - 35, GetColor(0, 255, 0), TRUE);
}


