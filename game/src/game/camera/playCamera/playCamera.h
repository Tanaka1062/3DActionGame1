#pragma once
#include <DxLib.h>
#include "../cameraBase.h"

class CPlayCamera : public CCameraBase
{
private:
	VECTOR m_focusPos;	//カメラの注視点

public:
	//コンストラクタ
	CPlayCamera();

	//初期化
	void Init();

	// 毎フレーム呼ぶ処理
	//_focus	:	プレイヤーの座標
	//_rot		:	プレイヤーの回転角度
	void Step(VECTOR _focus, float _rot);

	//カメラの更新
	// @_pos		:プレイヤーの座標
	void Update(VECTOR _pos);

private:

	//カメラの回転処理
	void Rotate(VECTOR _focus);

	//カメラの移動処理
	void Move(VECTOR _focus, float _rot);

};

