#pragma once
#include <DxLib.h>

class CDownCamera
{
private:
	VECTOR m_cameraPos;	// カメラの位置
	VECTOR m_tagetPos;	//カメラの注視点
	VECTOR m_upVec;		// カメラ上方向
	VECTOR m_rot;		//カメラの回転値

public:
	//コンストラクタ
	CDownCamera();

	//初期化
	void Init();

	//毎フレームする処理
	// @_vFocus		:プレイヤーの座標
	// @_fRotY		:プレイヤーの回転角度Y
	void Step(VECTOR _vFocus,float _fRotY);

	//カメラの更新
	void Update();

	//カメラの座標取得
	VECTOR GetPos() { return m_cameraPos; }

	//角度を取得
	VECTOR GetRot() { return m_rot; }
};

