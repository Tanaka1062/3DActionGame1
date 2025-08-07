#include "playScene.h"
#include "../../lib/collision/collision.h"
#include "../system/soundManager.h"
#include "../../lib/input/keyInput.h"


//---------------------------
//		コンストラクタ
//---------------------------
CPlayScene::CPlayScene() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//		デストラクタ
//---------------------------
CPlayScene::~CPlayScene() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}


//---------------------------
//		描画処理
//---------------------------
void CPlayScene::Draw()
{
	m_ground.Draw();
	m_sky.Draw();
	m_player.Draw();

	m_camera.Draw();


}

//---------------------------
//		初期化
//---------------------------
void CPlayScene::Init()
{
	m_ground.Init();
	m_sky.Init();
	m_camera.Init();
	m_player.Init();


}

//---------------------------
//		データ読み込み
//---------------------------
void CPlayScene::Load()
{
	m_ground.Load();
	m_sky.Load();
	m_player.Load();

}

//---------------------------
//		メイン処理
//---------------------------
void CPlayScene::Step()
{
	//各種計算処理を実行
	m_sky.Step();

	m_player.Step(m_camera.GetRot().y);

	m_camera.Step(m_player.GetPos(),m_player.GetRot().y);
	//当たり判定


	//すべての結果を反映させる
	m_ground.Update();
	m_sky.Update();
	m_camera.Update();
	m_player.Update();

	if (CKeyInput::IsTrg(KEY_SELECT) == true)
	{
		m_state = END;
	}

}

//---------------------------
//		終了前処理
//---------------------------
void CPlayScene::Exit()
{
	m_ground.Exit();
	m_sky.Exit();
	m_player.Exit();

	CSoundManager::StopAll();
}
