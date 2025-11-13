#include "powerCoinManager.h"

static const char* MODEL_PATH[COIN_NUM] = {
	"data/model/item/powerCoin/powerCoinRed.mv1",
	"data/model/item/powerCoin/powerCoinGreen.mv1",
	"data/model/item/powerCoin/powerCoinBlue.mv1" ,

};

static const char FRAME_PATH[] =
{ "data/model/map/TestMap4FramePos.mv1" };			//ロードするファイル名

static const int SPAWN_TIME = 10 * 60;				//コインスポーン時間(秒)

//------------------------
//	    コンストラクタ
//------------------------
CPowerCoinManager::CPowerCoinManager()
{
	//コインを生成
	for (int powerCoin_i = 0; powerCoin_i < COIN_NUM; powerCoin_i++)
	{
		CPowerCoin* coin = new CPowerCoin;
		m_powerCoin.push_back(coin);
	}

	//時間のリセット
	m_timeCount = 0;

	//スポーン座標初期化
	for (int spawnPos_i = 0; spawnPos_i < COIN_SPAWN_POS_NUM; spawnPos_i++)
	{
		m_spawnPos[spawnPos_i] = { 0.0f,0.0f,0.0f };
	}
}

//------------------------
//		デストラクタ
//------------------------
CPowerCoinManager::~CPowerCoinManager()
{
	for (auto powerCoin_ite = m_powerCoin.begin(); powerCoin_ite != m_powerCoin.end();)
	{
		delete (*powerCoin_ite);

		powerCoin_ite = m_powerCoin.erase(powerCoin_ite);
	}

}

//------------------------
//		  初期化
//------------------------
void CPowerCoinManager::Init()
{
	//コインの初期化
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Init();
	}

	//時間のリセット
	m_timeCount = 0;

	//スポーン座標初期化
	for (int spawnPos_i = 0; spawnPos_i < COIN_SPAWN_POS_NUM; spawnPos_i++)
	{
		m_spawnPos[spawnPos_i] = { 0.0f,0.0f,0.0f };
	}

}

//------------------------
//		モデルロード
//------------------------
void CPowerCoinManager::Load()
{
	//コインのモデルロード
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->LoadModel(MODEL_PATH[powerCoin_i]);
	}

	//マップのフレームのハンドルをロード
	int frameHndl = MV1LoadModel(FRAME_PATH);

	//スポーン座標をボーンから取得
	for (int spawnPos_i = 0; spawnPos_i < COIN_SPAWN_POS_NUM; spawnPos_i++)
	{
		//コイン出現位置を保存
		VECTOR start = { 0.0f,0.0f,0.0f };

		switch (spawnPos_i)
		{
		case COIN_SPAWN_POS_1:
			start = MV1GetFramePosition(frameHndl, 11);
			break;
		case COIN_SPAWN_POS_2:
			start = MV1GetFramePosition(frameHndl, 13);
			break;
		case COIN_SPAWN_POS_3:
			start = MV1GetFramePosition(frameHndl, 15);
			break;
		case COIN_SPAWN_POS_4:
			start = MV1GetFramePosition(frameHndl, 17);
			break;
		}
		m_spawnPos[spawnPos_i] = start;
	}
}

//------------------------
//	毎フレームする処理
//------------------------
void CPowerCoinManager::Step()
{
	//出現しているコインを数える
	int activeCoinNum = 0;

	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		//生存していたらカウントする
		if (m_powerCoin[powerCoin_i]->GetActive())
		{
			activeCoinNum++;
		}

		m_powerCoin[powerCoin_i]->Step();
	}

	//出現しているコインが最大数よりも少なかったらスポーンさせる
	if (activeCoinNum < COIN_NUM)
	{
		//時間を進める
		m_timeCount++;

		//スポーンする時間になったら出現させる
		if (m_timeCount >= SPAWN_TIME)
		{
			SpawnCoin();
			m_timeCount = 0;
		}
	}

}

//------------------------
//		数値の更新
//------------------------
void CPowerCoinManager::Update()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Update();
	}
}

//------------------------
//		  描写処理
//------------------------
void CPowerCoinManager::Draw()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Draw();
	}
}

//------------------------
//		   終了処理
//------------------------
void CPowerCoinManager::Exit()
{
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		m_powerCoin[powerCoin_i]->Exit();
	}
}

//------------------------
//	 コインを出現させる
//------------------------
void CPowerCoinManager::SpawnCoin()
{
	//ランダムな変数保存用
	int rand = GetRand(COIN_SPAWN_POS_NUM);

	//コインの出現
	for (int powerCoin_i = 0; powerCoin_i < m_powerCoin.size(); powerCoin_i++)
	{
		//生存していないコインを出現させる
		if (m_powerCoin[powerCoin_i]->GetActive() == false)
		{
			m_powerCoin[powerCoin_i]->SetPos(m_spawnPos[rand]);
			m_powerCoin[powerCoin_i]->SetActive(true);
			return;
		}
	}
}

