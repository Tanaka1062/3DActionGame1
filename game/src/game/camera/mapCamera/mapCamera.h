#pragma once
#pragma once
#include <DxLib.h>
#include "../cameraBase.h"
#include "../../map/mapBase.h"
#include "../../player/playerManager.h"
#include <iostream>
#include <vector>

class CMapCamera : public CCameraBase
{
private:
	std::vector<VECTOR>	m_stageCenterPos;
	VECTOR	m_basePos;			//ベースの座標
	VECTOR	m_nextPos;			//次の座標
	VECTOR	m_nextFocus;		//次の注視点
	enum tagCameraSate
	{
		MAP_MOVE_CAMERA,		//マップ移動用カメラ
		ZOOM_CAMERA,			//ズームカメラ

		CAMERA_STAE_NUM,		//カメラの状態の数
	};
	tagCameraSate m_state;		//カメラの状態
	int m_stageCenterId;		//ステージのId
	int m_nextPosTime;			//次の座標を更新するまでの時間

public:
	//コンストラクタ・デストラクタ
	CMapCamera();
	~CMapCamera();

	//初期化
	void Init(CMapBase* _map);

	// 毎フレーム呼ぶ処理
	void Step( int _stageCenterId,CPlayerManager* _playerManager);

	//カメラの更新
	void Update();

	//カメラの終了処理
	void Exit();

private:

	//カメラの回転処理
	void Rotate(VECTOR _focus);

	//カメラの移動処理
	void Move(int _stageCenterId, CPlayerManager* _playerManager);

};

