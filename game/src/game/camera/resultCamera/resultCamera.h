#pragma once
#pragma once
#include <DxLib.h>
#include "../cameraBase.h"
#include "../../map/mapBase.h"

class CResultCamera : public CCameraBase
{
private:
	VECTOR m_focusPos;	//カメラの注視点

public:
	//コンストラクタ
	CResultCamera();

	//初期化
	void Init(CMapBase* _map);

	// 毎フレーム呼ぶ処理
	void Step(VECTOR _focus, float _rot);

	//カメラの更新
	void Update();

private:

	//カメラの回転処理
	void Rotate(VECTOR _focus);

	//カメラの移動処理
	void Move(VECTOR _focus, float _rot);

};

