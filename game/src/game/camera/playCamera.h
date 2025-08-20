#pragma once
#include <DxLib.h>

class CPlayCamera
{
private:
	VECTOR m_cameraPos;	// カメラの位置
	VECTOR m_tagetPos;	//カメラの注視点
	VECTOR m_upVec;		// カメラ上方向
	VECTOR m_rot;		//カメラの回転値

public:
	//コンストラクタ
	CPlayCamera();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//カメラの更新
	// @_pos		:プレイヤーの座標
	void Update(VECTOR _pos);

	//カメラの座標取得
	VECTOR GetPos() { return m_cameraPos; }

	//角度を取得
	VECTOR GetRot() { return m_rot; }

private:

	//カメラの回転処理
	void Rotate();

};

