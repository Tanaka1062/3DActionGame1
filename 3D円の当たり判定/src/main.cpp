#include <crtdbg.h>
#include <memory>
#include "DxLib.h"
#include "collision.h"
#include "input/controllerInput.h"

//---------------------------------
// 立方体同士の当たり判定
//---------------------------------
bool CheckHitBoxToBox(VECTOR pos1, VECTOR size1,
	VECTOR pos2, VECTOR size2)
{
	// 四角形の上下左右手前奥それぞれの座標を計算する
	float up1 = pos1.y - size1.y * 0.5f;
	float down1 = pos1.y + size1.y * 0.5f;
	float left1 = pos1.x - size1.x * 0.5f;
	float right1 = pos1.x + size1.x * 0.5f;
	float front1 = pos1.z - size1.z * 0.5f;
	float back1 = pos1.z + size1.z * 0.5f;

	float up2 = pos2.y - size2.y * 0.5f;
	float down2 = pos2.y + size2.y * 0.5f;
	float left2 = pos2.x - size2.x * 0.5f;
	float right2 = pos2.x + size2.x * 0.5f;
	float front2 = pos2.z - size2.z * 0.5f;
	float back2 = pos2.z + size2.z * 0.5f;

	// 4つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (left1 <= right2 && right1 >= left2
		&& up1 <= down2 && down1 >= up2
		&& front1 <= back2 && back1 >= front2)
	{
		return true;
	}
	else return false;
}




// プログラムは WinMain から始まります
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク発見用
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// スクリーン設定
	ChangeWindowMode(TRUE);			// フルスクリーンorウィンドウモード
	SetGraphMode(1280, 720, 32);	// ウィンドウのサイズ
	
#ifndef _DEBUG
	// リリース版はログを出さない
	SetOutApplicationLogValidFlag(false);
#endif

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	//一番最初に１回だけやる処理
	SetDrawScreen(DX_SCREEN_BACK);


	//ゲームのインスタンスを生成
	int player1Hndl = MV1LoadModel("data/model/SphereChan/SphereChan.x");
	int player2Hndl = MV1LoadModel("data/model/SphereChan/SphereChanBig.x");

	//座標を設定
	VECTOR Player1Pos = { -10.0f,1.0f,0.0f };		//プレイヤー1の座標
	VECTOR Player2Pos = { 10.0f,1.0f,0.0f };		//プレイヤー2の座標



	//オブジェクトのサイズ設定
	float Player1R = 2.0f;							//プレイヤー1の半径
	float Player2R = 4.0f;							//プレイヤー2の半径

	//カメラ設定
	VECTOR cameraPos = { 0.0f, 7.0f, -20.0f };	// カメラの位置
	VECTOR targetPos = { 0.0f, 0.0f, 0.0f };
	VECTOR upVec = { 0.0f, 1.0f, 0.0f };		// カメラ上方向

	// カメラのニアーファー設定
	SetCameraNearFar(1.0f, 1000.0f);

	CControllerInput::Init();

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{

		//エスケープキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		ClearDrawScreen();	// 画面クリア

		//ここにゲームの本体を書く

		CControllerInput::Update();

		// プレイヤー1の移動========================
		float MOVE_SPEED = 0.1f;
		// 前後移動
		if (CheckHitKey(KEY_INPUT_W) != 0 &&
			CheckHitKey(KEY_INPUT_LSHIFT) != 0)
		{
			Player1Pos.y += MOVE_SPEED;
		}
		else if (CheckHitKey(KEY_INPUT_W) != 0 ||
			CControllerInput::IsTrg(PAD_INPUT_UP) == true)
		{
			Player1Pos.z += MOVE_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_S) != 0 &&
			CheckHitKey(KEY_INPUT_LSHIFT) != 0)
		{
			Player1Pos.y -= MOVE_SPEED;
		}
		else if (CheckHitKey(KEY_INPUT_S) != 0 ||
			CControllerInput::IsRep(PAD_INPUT_1) == true)
		{
			Player1Pos.z -= MOVE_SPEED;
		}
		// 左右移動
		if (CheckHitKey(KEY_INPUT_D) != 0)
		{
			Player1Pos.x += MOVE_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_A) != 0)
		{
			Player1Pos.x -= MOVE_SPEED;
		}


		// プレイヤー2の移動========================
		// 前後移動
		if (CheckHitKey(KEY_INPUT_W) != 0 &&
			CheckHitKey(KEY_INPUT_LSHIFT) != 0)
		{
			Player2Pos.y += MOVE_SPEED;
		}
		else if (CheckHitKey(KEY_INPUT_W) != 0)
		{
			Player2Pos.z += MOVE_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_S) != 0 &&
			CheckHitKey(KEY_INPUT_LSHIFT) != 0)
		{
			Player2Pos.y -= MOVE_SPEED;
		}
		else if (CheckHitKey(KEY_INPUT_S) != 0)
		{
			Player2Pos.z -= MOVE_SPEED;
		}
		// 左右移動
		if (CheckHitKey(KEY_INPUT_D) != 0)
		{
			Player2Pos.x += MOVE_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_A) != 0)
		{
			Player2Pos.x -= MOVE_SPEED;
		}


		//当たり判定
		if (CheckHitCircleToCircle(Player1Pos, Player1R, Player2Pos, Player2R) == true)
		{
			DrawFormatString(20, 20, GetColor(255, 0, 0), "当たってるんですけど");
		}


		// 移動結果をプレイヤーに設定
		MV1SetPosition(player1Hndl, Player1Pos);
		MV1SetPosition(player2Hndl, Player2Pos);
		//=========================================
		
		// カメラ設定
		SetCameraPositionAndTargetAndUpVec(cameraPos, targetPos, upVec);
		
		// モデル表示
		MV1DrawModel(player1Hndl);
		MV1DrawModel(player2Hndl);


		ScreenFlip();		// 描画切り替え

	}

	// モデル削除
	MV1DeleteModel(player1Hndl);
	MV1DeleteModel(player2Hndl);


	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

