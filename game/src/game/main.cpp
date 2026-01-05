#include <crtdbg.h>
#include <memory>
#include "DxLib.h"
#include "../lib/collision/collision.h"
#include "scene/playScene.h"
#include "scene/sceneManager.h"
#include "../lib/input/keyInput.h"
#include"data.h"
#include"../lib/system/fps.h"
#include"../lib/input/controllerManager.h"
#include"../lib/effekseer/effekseer.h"
#include"system/effectData/effectData.h"
#include "../lib/number.h"

constexpr int EFFECT_MAX_NUM = 10;			//一度に表示できるエフェクトの最大数
constexpr int PARTICLE_MAX_NUM = 2000;		//一度に表示できるパーティクルの最大数
static const char* GAME_NAME =					//ゲームのタイトル
"アクションゲーム";

// プログラムは WinMain から始まります
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク発見用
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// スクリーン設定
	ChangeWindowMode(TRUE);			// フルスクリーンorウィンドウモード
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);	// ウィンドウのサイズ
	
#ifndef _DEBUG
	// リリース版はログを出さない
	SetOutApplicationLogValidFlag(false);
#endif

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	//一番最初に１回だけやる処理
	SetDrawScreen(DX_SCREEN_BACK);
	SetMainWindowText(GAME_NAME);

	//当たり判定の球をきれいに表示
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	//シーンの初期化
	CSceneManager scene;

	//エフェクシアの初期化
	CEffekseerCtrl::Init(EFFECT_MAX_NUM,PARTICLE_MAX_NUM);

	//エフェクトデータの初期化
	CEffectData::Init();

	//エフェクトデータのロード
	CEffectData::Load();

	//キー入力の初期化
	CKeyInput::Init();
	//コントローラー入力の初期化
	CControllerManager::Init();
	//FPSの初期化
	CFps::Init();

	//数字の初期化
	CNumber::Init();

	//数字の画像ロード
	CNumber::Load();

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		//エスケープキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		//想定のフレームに到達していなければ処理を待つ
		if (CFps::IsNextFrame() == false)continue;

		ClearDrawScreen();	// 画面クリア

		//ここにゲームの本体を書く
		

		//シーンの実行処理
		scene.Loop();

		//キー入力の更新処理
		CKeyInput::Update();

		//コントローラー入力の更新処理
		CControllerManager::Update();

		//Fps更新処理
		CFps::Update();

		//シーンの描画処理
		scene.Draw();

		//エフェクシアの描画処理
		CEffekseerCtrl::Draw();

		//Fpsの表示
		CFps::Print();

		ScreenFlip();		// 描画切り替え

	}

	//エフェクシアの終了処理
	CEffekseerCtrl::Exit();

	//数字の終了処理
	CNumber::Exit();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

