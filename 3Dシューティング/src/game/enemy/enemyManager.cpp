#include "enemyManager.h"
#include "../../lib/effekseer.h"

//定義関連===========================
static const int ENEMY_NUM = 50;	//エネミーの数
static const char ENEMYT_MODEL_PATH[] ="data/model/enemy/enemy1.mv1";	//敵のモデルパス
static const char EFFECT_PATH[] = "data/effect/fire.efk";				//エフェクトのパス
static const int WAIT_TIME = 120;										//敵の再出現時間
static const int RESPAWN_LENGTH = 75;									//敵の出現する長さ
static const int MAX_SPEED = 5;											//敵の最高スピード
//===================================

//---------------------------
//		コンストラクタ
//---------------------------
CEnemyManager::CEnemyManager()
{
	Init();
}

//---------------------------
//		初期化
//---------------------------
void CEnemyManager::Init()
{
	if (m_enemy.size() != ENEMY_NUM)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			CEnemy enemy;
			enemy.Init();
			m_enemy.push_back(enemy);
		}
	}
	else
	{
		for (int i = 0; i < m_enemy.size(); i++)
		{
			m_enemy[i].Init();
		}
	}
	m_waitCount = 0;
	m_effectId = -1;

}

//---------------------------
//		ロード
//---------------------------
void CEnemyManager::Load()
{
	//オリジナルのモデルをロード
	int hndl = MV1LoadModel(ENEMYT_MODEL_PATH);

	//エフェクトのロード
	m_effectId = CEffekseerCtrl::LoadData(EFFECT_PATH);

	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i].Load(hndl,m_effectId);
	}

	//複製が終わったら即破棄
	MV1DeleteModel(hndl);

}

//---------------------------
//	毎フレームする処理
//---------------------------
void CEnemyManager::Step()
{
	//敵の処理
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i].Step();
	}
	//敵の出現処理
	m_waitCount--;
	if (m_waitCount <= 0)
	{
		//敵を出現
		Request();
		//待機時間を戻す
		m_waitCount = WAIT_TIME;
	}
}

//---------------------------
//		描写
//---------------------------
void CEnemyManager::Draw()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i].Draw();
	}

}

//---------------------------
//		終了処理
//---------------------------
void CEnemyManager::Exit()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i].Exit();
	}
}


//---------------------------
//		座標更新
//---------------------------
void CEnemyManager::Update()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i].Update();
	}

}

//---------------------------
//		敵をリクエスト
//---------------------------
void CEnemyManager::Request()
{
	VECTOR pos = { static_cast<float>(GetRand(RESPAWN_LENGTH * 2) - RESPAWN_LENGTH),10.0f,200.0f };
	VECTOR speed = { 0.0f,0.0f,(float)(-GetRand(MAX_SPEED - 1) - 1.0f) /10.0f};
	for (int i = 0; i < m_enemy.size(); i++)
	{
		//敵を出現
		if (m_enemy[i].Request(pos, speed))
		{
			//敵を出現させたら終了
			break;
		}
	}
}
