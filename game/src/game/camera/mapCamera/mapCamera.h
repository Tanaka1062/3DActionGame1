#pragma once
#pragma once
#include <DxLib.h>
#include "../cameraBase.h"
#include "../../map/map.h"
#include "../../player/playerManager.h"

class CMapCamera : public CCameraBase
{
private:
	VECTOR	m_mapCenterPos[MAP_CENTER_NUM];
	VECTOR	m_basePos;
	VECTOR	m_nextPos;
	VECTOR	m_nextFocus;
	enum tagCameraSate
	{
		MAP_MOVE_CAMERA,		//マップ移動用カメラ
		ZOOM_CAMERA,			//ズームカメラ

		CAMERA_STAE_NUM,		//カメラの状態の数
	};
	tagCameraSate m_state;
	tagMapCenterId m_mapCenterId;

public:
	//コンストラクタ
	CMapCamera();

	//初期化
	void Init(VECTOR _focus);

	// 毎フレーム呼ぶ処理
	void Step(VECTOR _focus, float _rot, tagMapCenterId _mapCenterId,CPlayerManager* _playerManager);

	//カメラの更新
	void Update();

private:

	//カメラの回転処理
	void Rotate(VECTOR _focus);

	//カメラの移動処理
	void Move(tagMapCenterId _mapCenterId, CPlayerManager* _playerManager);

};


