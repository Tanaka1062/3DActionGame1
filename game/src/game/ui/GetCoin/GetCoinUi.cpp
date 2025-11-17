#include "GetCoinUi.h"
#include "../../data.h"

static const char* GRAPHIC_PATH[COIN_NUM] =		//ロードするファイル名
{ 
	"data/graphic/ui/PowerCoinRedUi.mv1",
	"data/graphic/ui/PowerCoinGreenUi.mv1",
	"data/graphic/ui/PowerCoinBlueUi.mv1",

 };			

static const int GRAPHIC_NUM_X = 2;
static const int GRAPHIC_NUM_Y = 1;
static const int GRAPHIC_SIZE = 128;

CGetCoinUi::CGetCoinUi()
{
	m_pos = ZERO;

	for (int coinUi_i = 0; coinUi_i < COIN_NUM; coinUi_i++)
	{
		for (int graphic_i = 0; graphic_i < GRAPHIC_ALL_NUM; graphic_i++)
		{
			m_hndl[coinUi_i][graphic_i] = -1;
		}

		m_IsGetCoin[coinUi_i] = false;
	}

	m_powerCoinManager = nullptr;
}

CGetCoinUi::~CGetCoinUi()
{

}

//初期化
void CGetCoinUi::Init(VECTOR _pos, CPowerCoinManager* _powerCoinManager)
{
	m_pos = _pos;

	m_powerCoinManager = _powerCoinManager;

	for (int coinUi_i = 0; coinUi_i < COIN_NUM; coinUi_i++)
	{
		for (int graphic_i = 0; graphic_i < GRAPHIC_ALL_NUM; graphic_i++)
		{
			m_hndl[coinUi_i][graphic_i] = -1;
		}
		m_IsGetCoin[coinUi_i] = false;
	}
}

//ロード
void CGetCoinUi::Load()
{
	for (int coinUi_i = 0; coinUi_i < COIN_NUM; coinUi_i++)
	{
		LoadDivGraph(GRAPHIC_PATH[coinUi_i], GRAPHIC_ALL_NUM, GRAPHIC_NUM_X,
			GRAPHIC_NUM_Y, GRAPHIC_SIZE, GRAPHIC_SIZE, m_hndl[coinUi_i]);
	}
}

//毎フレームする処理
void CGetCoinUi::Step(tagPlayerName _playerName)
{
	for (int coin_i = 0; coin_i < m_powerCoinManager->GetPowerCoinNum(); coin_i++)
	{
		CPowerCoin* powerCoin = m_powerCoinManager->GetPowerCoin(coin_i);

		//プレイヤーの名前が引数と同じ場合フラグをtrueにする
		if (powerCoin->GetPlayerName() == _playerName)
		{
			m_IsGetCoin[coin_i] = true;
		}
		else
		{
			m_IsGetCoin[coin_i] = false;
		}

	}
}

//描写
void CGetCoinUi::Draw() 
{
	DrawRotaGraph(static_cast<int>(m_pos.x - 128.0f), static_cast<int>(m_pos.y),
		1.0f, 0.0f, m_hndl[0][m_IsGetCoin[0]], TRUE);
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0f, 0.0f, m_hndl[1][m_IsGetCoin[1]], TRUE);
	DrawRotaGraph(static_cast<int>(m_pos.x + 128.0f), static_cast<int>(m_pos.y),
		1.0f, 0.0f, m_hndl[2][m_IsGetCoin[2]], TRUE);

}

//破棄
void CGetCoinUi::Exit()
{
	for (int coinUi_i = 0; coinUi_i < COIN_NUM; coinUi_i++)
	{
		for (int graphic_i = 0; graphic_i < GRAPHIC_ALL_NUM; graphic_i++)
		{
			if (m_hndl[coinUi_i][graphic_i] != -1)
			{
				DeleteGraph(m_hndl[coinUi_i][graphic_i]);
				m_hndl[coinUi_i][graphic_i] = -1;
			}
		}
	}

}
