#pragma once
#include "playCamera.h"
#include "debugCamera.h"

//複数のカメラタイプを管理するクラス
class CCameraManager
{
public:

	//カメラタイプID
	enum tagCAMERA_ID
	{
		CAMERA_ID_PLAY,		//ゲームのメインカメラ
		CAMERA_ID_DOWN,		//見下ろし視点のカメラ
		CAMERA_ID_DEBUG,	//デバッグ時のカメラ

		CAMERA_ID_NUM,		//カメラのタイプの数
	};

private:
	CPlayCamera m_play;		//ゲームカメラ
	CDbugCamera m_debug;	//デバックカメラ
	tagCAMERA_ID m_id;		//カメラのタイプ
	VECTOR m_rot;			//カメラの回転値

public:

	//コンストラクタ
	CCameraManager();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

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

