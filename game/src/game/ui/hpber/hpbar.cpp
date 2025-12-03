#include "hpbar.h"

static const int HP_BAR_LEN = 630;		//HPバーの長さ		

//コンストラクタ・デストラクタ
CHpbar::CHpbar()
{
	Init();
}

CHpbar::~CHpbar()
{
	Exit();
}

//初期化
void CHpbar::Init(VECTOR _pos, float _rot)
{
	m_hpbar = 0.0f;
	m_hp = 0.0f;
	m_player = nullptr;
	C2DUi::Init(_pos, _rot);

}

//毎フレームする処理
void CHpbar::Step()
{
	//体力バーを１００で割る
	m_hpbar = static_cast<float>(0.01f * HP_BAR_LEN);
	
	//HPの割合をもとめる
	m_hp = static_cast<float>(m_player->GetHp()) / static_cast<float>(m_player->GetHpMax());

	//体力を求める
	m_hp = m_hp * m_hpbar * 100.0f;

}

//描写
void CHpbar::Draw(float _size)
{
	C2DUi::Draw(_size);

	DrawBox(static_cast<int>(m_pos.x - (HP_BAR_LEN * 0.5f)), static_cast<int>(m_pos.y + 26),
		static_cast<int>((m_pos.x - (HP_BAR_LEN * 0.5f)) + m_hp), static_cast<int>(m_pos.y - 14), GetColor(0, 255, 0), TRUE);

}


