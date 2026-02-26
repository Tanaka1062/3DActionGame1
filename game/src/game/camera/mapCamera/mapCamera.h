#pragma once
#pragma once
#include <DxLib.h>
#include "../cameraBase.h"
#include "../../map/map.h"

class CMapCamera : public CCameraBase
{
private:
	VECTOR m_mapCenterPos[MAP_CENTER_NUM];
	VECTOR m_basePos;
public:
	//コンストラクタ
	CMapCamera();

	//初期化
	void Init(VECTOR _focus);

	// 毎フレーム呼ぶ処理
	void Step(VECTOR _focus, float _rot, tagMapCenterId _mapCenterId,VECTOR _playerPos);

	//カメラの更新
	void Update();

private:

	//カメラの回転処理
	void Rotate(VECTOR _focus);

	//カメラの移動処理
	void Move(tagMapCenterId _mapCenterId);

};

