#include "GetCoinUi.h"
#include "../../data.h"

static const char* GRAPHIC_PATH[COIN_MAX_NUM] =		//ロードするファイル名
{ 
	"data/graphic/ui/PowerCoinRedUi.png",
	"data/graphic/ui/PowerCoinGreenUi.png",
	"data/graphic/ui/PowerCoinBlueUi.png",

 };			

static const int GRAPHIC_NUM_X = 2;
static const int GRAPHIC_NUM_Y = 1;
static const int GRAPHIC_SIZE = 32;

CGetCoinUi::CGetCoinUi()
{
	m_pos = ZERO;

	for (int coinUi_i = 0; coinUi_i < COIN_MAX_NUM; coinUi_i++)
	{
		for (int graphic_i = 0; graphic_i < GRAPHIC_ALL_NUM; graphic_i++)
		{
			m_hndl[coinUi_i][graphic_i] = -1;
		}

		m_IsGetCoin[coinUi_i] = false;
	}

	m_itemManager = nullptr;
}

CGetCoinUi::~CGetCoinUi()
{

}

//初期化
void CGetCoinUi::Init(VECTOR _pos, CItemManager* _itemManager)
{
	m_pos = _pos;

	m_itemManager = _itemManager;

	for (int coinUi_i = 0; coinUi_i < COIN_MAX_NUM; coinUi_i++)
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
	for (int coinUi_i = 0; coinUi_i < COIN_MAX_NUM; coinUi_i++)
	{
		LoadDivGraph(GRAPHIC_PATH[coinUi_i], GRAPHIC_ALL_NUM, GRAPHIC_NUM_X,
			GRAPHIC_NUM_Y, GRAPHIC_SIZE, GRAPHIC_SIZE, m_hndl[coinUi_i]);
	}
}

//毎フレームする処理
void CGetCoinUi::Step(tagPlayerName _playerName)
{
	for (int coin_i = 0; coin_i < COIN_MAX_NUM; coin_i++)
	{
		CPowerCoin* coin = m_itemManager->GetCoin(coin_i);

		//プレイヤーの名前が引数と同じ場合フラグをtrueにする
		if (coin->GetPlayerName() == _playerName)
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
	int coinNum = 0;
	for (int coin_i = 0; coin_i < COIN_MAX_NUM; coin_i++)
	{
		if (m_IsGetCoin[coin_i] == true)
		{
			coinNum++;
		}
	}

	if (coinNum >= COIN_MAX_NUM)return;

	DrawRotaGraph(static_cast<int>(m_pos.x - GRAPHIC_SIZE), static_cast<int>(m_pos.y),
		0.5f, 0.0f, m_hndl[0][m_IsGetCoin[0]], TRUE);
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		0.5f, 0.0f, m_hndl[1][m_IsGetCoin[1]], TRUE);
	DrawRotaGraph(static_cast<int>(m_pos.x + GRAPHIC_SIZE), static_cast<int>(m_pos.y),
		0.5f, 0.0f, m_hndl[2][m_IsGetCoin[2]], TRUE);

}

//破棄
void CGetCoinUi::Exit()
{
	for (int coinUi_i = 0; coinUi_i < COIN_MAX_NUM; coinUi_i++)
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
