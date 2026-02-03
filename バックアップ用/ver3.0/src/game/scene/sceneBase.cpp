#include "sceneBase.h"
#include "../data.h"

//---------------------------
//コンストラクタ
//---------------------------
CSceneBase::CSceneBase() {
	//最初はデータ初期化
	m_state = INIT;
}

//---------------------------
//デストラクタ
//---------------------------
CSceneBase::~CSceneBase() {
	//安全のためにデータ破棄処理を呼び出し
	Exit();
}

//---------------------------
//実行処理
//---------------------------
int CSceneBase::Loop()
{
	//ゲームが終了したかを外部に伝えるため
	int result = -1;

	switch (m_state)
	{
	case INIT:
		//初期化
		Init();

		m_state = LOAD;	//ロードに進む
		break;
	case LOAD:
		//データ読み込み
		Load();
		break;
	case MAIN:
		//メイン処理
		Step();
		break;
	case END:
		//終了前処理
		Exit();

		m_state = INIT;	//初期化に進む
		result = 0;
		break;
	}

	//本編が終了したかどうかを外部に伝える
	return result;
}

//---------------------------
//描画処理
//---------------------------
void CSceneBase::Draw()
{
}

//---------------------------
//初期化
//---------------------------
void CSceneBase::Init()
{
	m_LoadState = 0;

	VECTOR loadBGPos = ZERO;

	loadBGPos.x = WINDOW_SIZE_X * 0.5f;
	loadBGPos.y = WINDOW_SIZE_Y * 0.5f;

	m_LoadBG.Init(loadBGPos);
}

//---------------------------
//データ読み込み
//---------------------------
void CSceneBase::Load()
{
	m_LoadBG.Load("data/graphic/Load/Load.png");

	//非同期読み込みを行う
	SetUseASyncLoadFlag(TRUE);
}

//---------------------------
//メイン処理
//---------------------------
void CSceneBase::Step()
{

}

//---------------------------
//終了前処理
//---------------------------
void CSceneBase::Exit()
{

}
