#include "powerCoinManager.h"

static const VECTOR INIT_POS[COIN_NUM] = {
	{100.0f,0.0f,50.0f},
	{150.0f,0.0f,50.0f},
	{200.0f,0.0f,50.0f},

};




CPowerCoinManager::CPowerCoinManager()
{
	for (int powerCoin_i = 0; powerCoin_i < COIN_NUM; powerCoin_i++)
	{
		CPowerCoin* coin = new CPowerCoin;
		m_powerCoin.push_back(coin);
	}
}

CPowerCoinManager::~CPowerCoinManager()
{
	for (auto powerCoin_ite = m_powerCoin.begin(); powerCoin_ite != m_powerCoin.end();)
	{
		delete (*powerCoin_ite);

		powerCoin_ite = m_powerCoin.erase(powerCoin_ite);
	}

}

//初期化
void CPowerCoinManager::Init()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Init();

		m_powerCoin[powerCoin_i]->SetPos(INIT_POS[powerCoin_i]);
	}
}

//モデルロード
void CPowerCoinManager::Load()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->LoadModel();
	}
}

//毎フレームする処理
void CPowerCoinManager::Step()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Step();
	}
}

//数値の更新
void CPowerCoinManager::Update()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Update();
	}
}

//描写処理
void CPowerCoinManager::Draw()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Draw();
	}
}

//終了処理
void CPowerCoinManager::Exit()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Exit();
	}
}

