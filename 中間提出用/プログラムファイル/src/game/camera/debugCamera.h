#pragma once
#include <DxLib.h>

class CDbugCamera
{
private:
	VECTOR m_cameraPos;	// カメラの位置
	VECTOR m_upVec;		// カメラ上方向
	VECTOR m_rot;		//回転角度


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

	//カメラの移動
	void Move();

	//カメラの回転
	void Rotate();

	//カメラの座標と注視点を設定
	// _vCameraPos		:カメラの座標
	// _vRot			:カメラの角度
	void SetPos(VECTOR _vCameraPos,VECTOR _vRot)
	{
		m_cameraPos = _vCameraPos;
		m_rot = _vRot;
	}

};

