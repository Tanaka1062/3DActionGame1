#include "enemyManager.h"
#include "enemyRootData.h"
#include "flyEnemy/flyEnemy.h"

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
	m_rootHndl = -1;

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (m_enemy.size() < ENEMY_NUM) 
		{
			if (i == 0)
				m_enemy.push_back(new CFlyEnemy);
			else
				m_enemy.push_back(new CEnemy);
		}
		m_enemy[i]->Init();
		//ルートを設定
		for (int j = 0; j < ENEMY_ROOT_MAX; j++)
		{
			//ルートが-1なら処理を終了
			if (ENEMY_ROOT[i][j] == -1)continue;

			m_enemy[i]->SetRoot(ENEMY_ROOT[i][j]);
		}
	}


}

//------------------------
//	オブジェクトのロード
//------------------------
void CEnemyManager::Load()
{
	if (m_rootHndl == -1)
	{
		m_rootHndl = MV1LoadModel("data/model/map/map1FramePos.mv1");
	}

	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Load(m_rootHndl);
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


