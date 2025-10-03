#pragma once
#include <DxLib.h>
#include "../cameraBase.h"

class CPlayCamera : public CCameraBase
{
private:
	VECTOR m_tagetPos;	//カメラの注視点

public:
	//コンストラクタ
	CPlayCamera();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//カメラの更新
	// @_pos		:プレイヤーの座標
	void Update(VECTOR _pos);

private:

	//カメラの回転処理
	void Rotate();

};

