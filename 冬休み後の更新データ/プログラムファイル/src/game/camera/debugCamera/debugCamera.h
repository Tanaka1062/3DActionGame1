#pragma once
#include <DxLib.h>
#include "../cameraBase.h"

class CDbugCamera : public CCameraBase
{
private:

public:
	//コンストラクタ
	CDbugCamera();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//テキスト表示
	void Draw();

	//カメラの更新
	void Update();

private:

	//カメラの移動
	void Move();

	//カメラの回転
	void Rotate();

};

