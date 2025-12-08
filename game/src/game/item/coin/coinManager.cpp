#include "coinManager.h"

static const char* MODEL_PATH[COIN_NUM] = {
	"data/model/item/powerCoin/powerCoinRed.mv1",
	"data/model/item/powerCoin/powerCoinGreen.mv1",
	"data/model/item/powerCoin/powerCoinBlue.mv1" ,

};

static const char FRAME_PATH[] =
{ "data/model/map/TestMap6Frame.mv1" };			//ロードするファイル名

static const int SPAWN_TIME = 10 * 60;				//コインスポーン時間(秒)

//------------------------
//	   コンストラクタ
//------------------------
CCoinManager::CCoinManager()
{
	//コインを生成
	for (int powerCoin_i = 0; powerCoin_i < COIN_NUM; powerCoin_i++)
	{
		CCoin* coin = new CCoin;
		m_coin.push_back(coin);
	}

	//時間のリセット
	m_timeCount = 0;

	//スポーン座標初期化
	for (int spawnPos_i = 0; spawnPos_i < COIN_SPAWN_POS_NUM; spawnPos_i++)
	{
		m_spawnPos[spawnPos_i] = { 0.0f,0.0f,0.0f };
	}

	m_playerManager = nullptr;
}

//------------------------
//		デストラクタ
//------------------------
CCoinManager::~CCoinManager()
{
	for (auto powerCoin_ite = m_coin.begin(); powerCoin_ite != m_coin.end();)
	{
		delete (*powerCoin_ite);

		powerCoin_ite = m_coin.erase(powerCoin_ite);
	}

}

//------------------------
//		  初期化
//------------------------
void CCoinManager::Init(CPlayerManager* _playerManager)
{
	//コインの初期化
	for (int powerCoin_i = 0; powerCoin_i < m_coin.size(); powerCoin_i++)
	{
		m_coin[powerCoin_i]->Init();
	}

	//時間のリセット
	m_timeCount = 0;

	//スポーン座標初期化
	for (int spawnPos_i = 0; spawnPos_i < COIN_SPAWN_POS_NUM; spawnPos_i++)
	{
		m_spawnPos[spawnPos_i] = { 0.0f,0.0f,0.0f };
	}

	m_playerManager = _playerManager;
}

//------------------------
//		モデルロード
//------------------------
void CCoinManager::Load()
{
	//コインのモデルロード
	for (int powerCoin_i = 0; powerCoin_i < m_coin.size(); powerCoin_i++)
	{
		m_coin[powerCoin_i]->Load(MODEL_PATH[powerCoin_i]);
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
void CCoinManager::Step()
{
	//出現しているコインを数える
	int activeCoinNum = 0;

	for (int powerCoin_i = 0; powerCoin_i < m_coin.size(); powerCoin_i++)
	{
		//生存していたらカウントする
		if (m_coin[powerCoin_i]->GetActive())
		{
			activeCoinNum++;

			m_coin[powerCoin_i]->Step();
		}

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

	//コインをドロップしていたら落とす
	for (int player_i = 0; player_i < m_playerManager->GetPlayerNum(); player_i++)
	{
		CPlayer* player = m_playerManager->GetPlayer(player_i);


		if (player->GetDropCoin() >= 1)
		{
			for (int powerCoin_i = 0; powerCoin_i < m_coin.size(); powerCoin_i++)
			{
				//コインが全てドロップ状態になったら一つ消す
				if (player->GetDropCoin() == COIN_NUM)
				{
					m_coin[powerCoin_i]->Delete();
				}

				//プレイヤーの持っているコインがある場合落とす
				if (m_coin[powerCoin_i]->GetPlayerName() == player->GetPlayerName())
				{

					float radian = static_cast<float>((GetRand(60) - 30) * (DX_PI_F/180.0f));

					//とりあえず中心に飛ばす
					float rotY = atan2f(-player->GetPos().x, -player->GetPos().z);

					rotY += radian;

					m_coin[powerCoin_i]->Drop(player->GetCenter(),rotY);
					break;
				}
			}
			//一ずつ減らす
			player->SetDropCoin(player->GetDropCoin() - 1);
		}
	}
}

//------------------------
//		数値の更新
//------------------------
void CCoinManager::Update()
{
	for (int powerCoin_i = 0; powerCoin_i < m_coin.size(); powerCoin_i++)
	{
		if (m_coin[powerCoin_i]->GetActive() == false)continue;

		m_coin[powerCoin_i]->Update();
	}
}

//------------------------
//		  描写処理
//------------------------
void CCoinManager::Draw()
{
	for (int powerCoin_i = 0; powerCoin_i < m_coin.size(); powerCoin_i++)
	{
		m_coin[powerCoin_i]->Draw();
	}
}

//------------------------
//		   終了処理
//------------------------
void CCoinManager::Exit()
{
	for (int powerCoin_i = 0; powerCoin_i < m_coin.size(); powerCoin_i++)
	{
		m_coin[powerCoin_i]->Exit();
	}
}

//------------------------
//	 コインを出現させる
//------------------------
void CCoinManager::SpawnCoin()
{
	//ランダムな変数保存用
	int rand = GetRand(COIN_SPAWN_POS_NUM -1);

	//コインの出現
	for (int powerCoin_i = 0; powerCoin_i < m_coin.size(); powerCoin_i++)
	{
		//生存していないコインを出現させる
		if (m_coin[powerCoin_i]->GetActive() == false &&
			m_coin[powerCoin_i]->GetPlayerName() == PLAYER_NONE)
		{
			m_coin[powerCoin_i]->SetPos(m_spawnPos[rand]);
			m_coin[powerCoin_i]->SetActive(true);
			return;
		}
	}
}

