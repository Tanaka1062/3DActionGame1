#include "playScene.h"
#include "../../lib/collision/collision.h"
#include "../system/soundManager.h"
#include "../../lib/input/keyInput.h"
#include"../player/player.h"



//---------------------------
//コンストラクタ
//---------------------------
CPlayScene::CPlayScene() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//デストラクタ
//---------------------------
CPlayScene::~CPlayScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}


//---------------------------
//描画処理
//---------------------------
void CPlayScene::Draw()
{
	m_ground.Draw();
	m_sky.Draw();
	

	m_camera.Draw();


}

//---------------------------
//初期化
//---------------------------
void CPlayScene::Init()
{
	m_ground.Init();
	m_sky.Init();
	m_camera.Init();

	//プレイヤーの初期化
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_chara.push_back(new CPlayer);
		m_chara[i]->SetType(TYPE_PLAYER);
	}


}

//---------------------------
//データ読み込み
//---------------------------
void CPlayScene::Load()
{
	m_ground.Load();
	m_sky.Load();

	for (int i = 0; i < m_chara.size(); i++)
	{
		m_chara[i]->Load();
	}
}

//---------------------------
//メイン処理
//---------------------------
void CPlayScene::Step()
{
	//各種計算処理を実行
	m_sky.Step();

	for (int i = 0; i < m_chara.size(); i++)
	{
		m_chara[i]->Step();
	}

	m_camera.Step(m_chara[0]->GetPos(),m_chara[0]->GetRot().y);
	//当たり判定


	//すべての結果を反映させる
	m_ground.Update();
	m_sky.Update();
	m_camera.Update();

	for (int i = 0; i < m_chara.size(); i++)
	{
		m_chara[i]->Update();
	}

	if (CKeyInput::IsTrg(KEY_SELECT) == true)
	{
		m_state = END;
	}

}

//---------------------------
//終了前処理
//---------------------------
void CPlayScene::Exit()
{
	m_ground.Exit();
	m_sky.Exit();

	//キャラクターの終了処理
	for (int i = 0; i < m_chara.size(); i++)
	{
		m_chara[i]->Exit();

		delete m_chara[i];
	}

	//キャラクターの要素削除
	for (int i = 0; i < m_chara.size(); i++)
	{
		m_chara.pop_back();
	}

	CSoundManager::StopAll();
}
