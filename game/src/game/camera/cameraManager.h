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
	CPlayCamera m_play;
	CDbugCamera m_debug;
	tagCAMERA_ID m_id;

public:

	//コンストラクタ
	CCameraManager();

	//初期化
	void Init();

	//毎フレームする処理
	// @_vFocus	:プレイヤーの座標
	// @_fRotY		:プレイヤーの回転角度Y
	void Step(VECTOR _vFocus, float _fRotY);

	//表示
	void Draw();

	//カメラの更新
	void Update();

	//カメラのタイプ切り替え
	void ChangeCamera(tagCAMERA_ID _id) { m_id = _id; };
	//カメラタイプの取得
	tagCAMERA_ID GetID() { return m_id; }

};

