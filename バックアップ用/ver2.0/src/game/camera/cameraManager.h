#pragma once
#include "playCamera/playCamera.h"
#include "debugCamera/debugCamera.h"
#include "mapCamera/mapCamera.h"
#include "cameraBase.h"

//複数のカメラタイプを管理するクラス
class CCameraManager
{
public:

	//カメラタイプID
	enum tagCAMERA_ID
	{
		CAMERA_ID_PLAY,						//ゲームのメインカメラ
		CAMERA_ID_MAP,						//マップのカメラ
		CAMERA_ID_DEBUG,					//デバッグ時のカメラ

		CAMERA_ID_NUM,						//カメラのタイプの数
	};

private:
	CCameraBase* m_camera[CAMERA_ID_NUM];	//カメラ
	tagCAMERA_ID m_id;						//カメラのタイプ
	VECTOR m_rot;							//カメラの回転値

public:

	//コンストラクタ
	CCameraManager();

	//初期化
	void Init(VECTOR _focus);

	//毎フレームする処理
	void Step(VECTOR _focus, float _rot);

	//表示
	void Draw();

	//カメラの更新
	// @_tagetPos	:カメラの注視点の座標
	void Update(VECTOR _tagetPos);

	//カメラのタイプ切り替え
	void ChangeCamera(tagCAMERA_ID _id) { m_id = _id; };
	//カメラタイプの取得
	tagCAMERA_ID GetID() { return m_id; }

	//カメラの回転値の取得
	VECTOR  GetRot() { return m_rot; }

};

