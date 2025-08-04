#include "3DActorManager.h"


//---------------------------
//		コンストラクタ
//---------------------------
//C3DActorManager::C3DActorManager()
//{
//	Init();
//}

//---------------------------
//		初期化
//---------------------------
//void C3DActorManager::Init()
//{
//	m_actMax = 0;
//	for (int i = 0; i < m_actMax; i++)
//	{
//		m_enemy[i].Init();
//	}
//
//}
//
////---------------------------
////		ロード
////---------------------------
//void C3DActorManager::Load()
//{
//	//オリジナルのモデルをロード
//	int hndl = MV1LoadModel(ENEMYT_MODEL_PATH);
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		m_enemy[i].Load(hndl);
//	}
//
//	//複製が終わったら即破棄
//	MV1DeleteModel(hndl);
//}
//
////---------------------------
////	毎フレームする処理
////---------------------------
//void C3DActorManager::Step()
//{
//	//敵の処理
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		m_enemy[i].Step();
//	}
//	//敵の出現処理
//	m_waitCount--;
//	if (m_waitCount <= 0)
//	{
//		//敵を出現
//		Request();
//		//待機時間を戻す
//		m_waitCount = WAIT_TIME;
//	}
//}
//
////---------------------------
////		描写
////---------------------------
//void C3DActorManager::Draw()
//{
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		m_enemy[i].Draw();
//	}
//
//}
//
////---------------------------
////		終了処理
////---------------------------
//void C3DActorManager::Exit()
//{
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		m_enemy[i].Exit();
//	}
//}
//
//
////---------------------------
////		座標更新
////---------------------------
//void C3DActorManager::Update()
//{
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		m_enemy[i].Update();
//	}
//
//}
//
////---------------------------
////		敵をリクエスト
////---------------------------
//void C3DActorManager::Request()
//{
//	VECTOR pos = { (float)GetRand(200) - 100.0f,10.0f,200.0f };
//	VECTOR speed = { 0.0f,0.0f,(float)(-GetRand(4) - 1.0f) /10.0f};
//	for (int i = 0; i < ENEMY_NUM; i++)
//	{
//		//敵を出現
//		if (m_enemy[i].Request(pos, speed))
//		{
//			//敵を出現させたら終了
//			break;
//		}
//	}
//}
