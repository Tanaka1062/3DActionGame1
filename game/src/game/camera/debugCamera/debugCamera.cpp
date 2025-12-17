#include "debugCamera.h"
#include <math.h>

//定義関連====================================
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr float CAMERA_BACK = 40.0f;				//カメラとプレイヤーの距離
constexpr float CAMERA_OFFSET_Y = 40.0f;			//カメラの修正Y
constexpr float TARGET_OFFSET_Y = 20.0f;			//ターゲットの修正Y
constexpr float CAMERA_SPEED = 4.0f;				//カメラの移動速度
constexpr float CAMERA_ROT_SPEED = 0.01f;			//カメラの回転速度
//============================================

//コンストラクタ
CDbugCamera::CDbugCamera() 
{
	Init();
}

//初期化
void CDbugCamera::Init()
{
	CCameraBase::Init(ZERO);
}

//毎フレームする処理
void CDbugCamera::Step()
{
	//カメラの移動
	Move();

	//カメラの回転
	Rotate();

}

//テキスト表示
void CDbugCamera::Draw()
{
	DrawFormatString(32,32,GetColor(255,0,0),"デバックカメラモード");

	VECTOR vRot;
	vRot.x = m_rot.x * (180 / DX_PI_F);
	vRot.y= m_rot.y * (180 / DX_PI_F);
	vRot.z = m_rot.z * (180 / DX_PI_F);


	DrawFormatString(32, 100, GetColor(255, 0, 0),
		"角度X = %f\n角度Y = %f\n角度Z = %f\n",
		vRot.x, vRot.y, vRot.z);

}


//カメラの更新
void CDbugCamera::Update()
{
	// カメラ設定
	SetCameraPositionAndAngle(m_pos, m_rot.x, m_rot.y, m_rot.z);
}

//カメラの移動
void CDbugCamera::Move()
{

	//前後移動処理=================================
	
	//前進
	float speed = 0.0f;		//実際の速度
	if (CheckHitKey(KEY_INPUT_W) != 0)
	{
		speed = CAMERA_SPEED;

	}
	//後退
	if (CheckHitKey(KEY_INPUT_S) != 0)
	{
		speed = -CAMERA_SPEED;
	}

	//カメラの角度がオールゼロの時に進む速度
	VECTOR defaultDir = { 0.0f,0.0f,speed };
	//上記を行列に変換
	MATRIX dir = MGetTranslate(defaultDir);
	//X軸回転行列
	MATRIX mRotX = MGetRotX(m_rot.x);
	//Y軸回転行列
	MATRIX mRotY = MGetRotY(m_rot.y);
	//行列の合成
	MATRIX res = MMult(dir, mRotX);
	res = MMult(res, mRotY);

	//行列から移動情報だけを取り出す
	VECTOR move;
	move.x = res.m[3][0];
	move.y = res.m[3][1];
	move.z = res.m[3][2];
	//計算結果をカメラの現在の座標に足す
	m_pos = VAdd(m_pos, move);

	//=============================================

	//左右移動処理=================================

	//左移動
	speed = 0.0f;		//実際の速度
	if (CheckHitKey(KEY_INPUT_A) != 0)
	{
		speed = -CAMERA_SPEED;
	}
	//右移動
	if (CheckHitKey(KEY_INPUT_D) != 0)
	{
		speed = CAMERA_SPEED;
	}
	float rotY = m_rot.y + (90 * (DX_PI_F / 180));

	m_pos.x += sinf(rotY) * speed;
	m_pos.z += cosf(rotY) * speed;

	//=============================================

}

//カメラの回転
void CDbugCamera::Rotate()
{
	//上を向く
	if (CheckHitKey(KEY_INPUT_UP) != 0)
	{
		m_rot.x -= CAMERA_ROT_SPEED;
	}
	//下を向く
	if (CheckHitKey(KEY_INPUT_DOWN) != 0)
	{
		m_rot.x += CAMERA_ROT_SPEED;
	}

	float rotX = m_rot.x * (180/DX_PI_F);
	if (rotX >= 90)
	{
		m_rot.x = (90 * (DX_PI_F / 180));
	}
	else if (rotX <= -90)
	{
		m_rot.x = (-90 * (DX_PI_F / 180));
	}


	//右を向く
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
	{
		m_rot.y += CAMERA_ROT_SPEED;
	}
	//左を向く
	if (CheckHitKey(KEY_INPUT_LEFT) != 0)
	{
		m_rot.y -= CAMERA_ROT_SPEED;
	}


}

