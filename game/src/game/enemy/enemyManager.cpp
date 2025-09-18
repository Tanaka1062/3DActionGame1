#include "enemyManager.h"

static const int ENEMY_NUM = 2;			//敵の数

//------------------------
//	  コンストラクタ
//------------------------
CEnemyManager::CEnemyManager()
{
	Init();
}

//------------------------
//	  デストラクタ
//------------------------
CEnemyManager::~CEnemyManager()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		delete m_enemy[i];
	}

}

//------------------------
//		  初期化
//------------------------
void CEnemyManager::Init()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (m_enemy.size() < ENEMY_NUM) 
		{
			m_enemy.push_back(new CEnemy);
		}
		VECTOR initPos = { 0.0f,1.0f,20.0f };
		initPos.x = static_cast<float>(10 * i);
		m_enemy[i]->Init(initPos);
	}
}

//------------------------
//	オブジェクトのロード
//------------------------
void CEnemyManager::Load()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Load();
	}
}

//------------------------
//	毎フレームする処理
//------------------------
void CEnemyManager::Step(VECTOR _pos)
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Step(_pos);
	}
}

//------------------------
//		 数値の更新
//------------------------
void CEnemyManager::Update()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CEnemyManager::Draw()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Draw();
	}
}


//------------------------
//		  終了処理
//------------------------
void CEnemyManager::Exit()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_enemy[i]->Exit();

	}
	
}


