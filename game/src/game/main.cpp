#include <crtdbg.h>
#include <memory>
#include "DxLib.h"
#include "../lib/collision/collision.h"
#include "scene/playScene.h"
#include "scene/sceneManager.h"
#include "../lib/input/keyInput.h"
#include"data.h"
#include"../lib/system/fps.h"

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

	//当たり判定の球をきれいに表示
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	//シーンの初期化
	CSceneManager scene;

	//キー入力の初期化
	CKeyInput::Init();
	//FPSの初期化
	CFps::Init();

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
		
		//Fps更新処理
		CFps::Update();

		scene.Draw();

		//Fpsの表示
		CFps::Print();


		ScreenFlip();		// 描画切り替え

	}


	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

