#include "PlayCamera.h"
#include <math.h>
#include"../../lib/input/keyInput.h"
#include"../../lib/input/controllerManager.h"

//定義関連====================================
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
static const float CAMERA_OFFSET_Y = 10.0f;			//カメラの修正Y
static const float TARGET_OFFSET_Y = 2.0f;			//ターゲットの修正Y

static const float MAX_LEN_NEAR = 30.0f;			//この距離より離れるとカメラ移動開始
static const float MAX_LEN_FAR = 35.0f;				//これ以上は離させない
static const float MIN_LEN_NEAR = 25.0f;			//この距離より近づくとカメラ移動開始
static const float MIN_LEN_FAR = 20.0f;				//これ以上は近づけさせない
static const float CAMERA_MOVE_SPEED = 0.5f;		//カメラのデフォルト移動速度
static const float CAMERA_ROT_SPEED = 2.0f;			//カメラの回転速度
//============================================

//---------------------------------
//		コンストラクタ
//---------------------------------
CPlayCamera::CPlayCamera() {
	Init(ZERO);
}

//---------------------------------
//			初期化
//---------------------------------
void CPlayCamera::Init(VECTOR _focus)
{
	CCameraBase::Init(_focus);
	m_focusPos = _focus;						//カメラの注視点

	m_pos = _focus;
	m_pos.z += MAX_LEN_NEAR;
	
}

//---------------------------------
//		毎フレームする処理
//---------------------------------
void CPlayCamera::Step(VECTOR _focus, float _rot)
{
	//カメラ回転処理
	Rotate(_focus);

	//カメラ移動処理
	Move(_focus,_rot);

}

//---------------------------------
//			カメラの更新
//---------------------------------
void CPlayCamera::Update(VECTOR _pos)
{

	// カメラ設定更新
	SetCameraPositionAndTargetAndUpVec(m_pos, m_focusPos, m_upVec);

}

//---------------------------------
//			カメラの回転処理
//---------------------------------
void CPlayCamera::Rotate(VECTOR _focus)
{
	//コントローラー用カメラ回転
	if (CControllerManager::GetRX() != 0)
	{
		//スティックを入力した力分だけ回転速度を取得する
		float rotSpeed = CAMERA_ROT_SPEED * CControllerManager::GetRX();

		//外積を計算するための１つめのベクトル
		VECTOR v1 = { 0.0f,1.0f,0.0f };
		//今いるところから注視点に向かうベクトル
		VECTOR v2 = VSub(m_pos, _focus);
		//上記のベクトルを使って垂直な法線を計算
		VECTOR v3 = VCross(v1, v2);
		//正規化して長さを一定にする
		v3 = VNorm(v3);
		v3 = VScale(v3, rotSpeed);
		//計算結果を今の位置に足す
		m_pos = VAdd(m_pos, v3);

	}

	if (CheckHitKey(CheckHitKey(KEY_INPUT_RIGHT) != 0))
	{
		//外積を計算するための１つめのベクトル
		VECTOR v1 = { 0.0f,1.0f,0.0f };
		//今いるところから注視点に向かうベクトル
		VECTOR v2 = VSub(m_pos, _focus);
		//上記のベクトルを使って垂直な法線を計算
		VECTOR v3 = VCross(v1, v2);
		//正規化して長さを一定にする
		v3 = VNorm(v3);
		v3 = VScale(v3, CAMERA_ROT_SPEED);
		//計算結果を今の位置に足す
		m_pos = VAdd(m_pos, v3);

	}
	else if (CheckHitKey(KEY_INPUT_LEFT) != 0)
	{
		//外積を計算するための１つめのベクトル
		VECTOR v1 = { 0.0f,1.0f,0.0f };
		//今いるところから注視点に向かうベクトル
		VECTOR v2 = VSub(m_pos, _focus);
		//上記のベクトルを使って垂直な法線を計算
		VECTOR v3 = VCross(v2, v1);
		//正規化して長さを一定にする
		v3 = VNorm(v3);
		v3 = VScale(v3, CAMERA_ROT_SPEED);
		//計算結果を今の位置に足す
		m_pos = VAdd(m_pos, v3);
	}

}

//カメラの移動処理
void CPlayCamera::Move(VECTOR _focus, float _rot)
{
	////現在のカメラの位置からキャラクターの位置までの方向ベクトルを取得
	VECTOR dir = VSub(m_pos, _focus);
	dir.y = 0.0f;	//高さを配慮するとややこしいので,一旦無視

	//今回は長さが重要なので、先ほど計算したベクトルから長さを計算
	float len = VSize(dir);
	//長さを求めたので、方向ベクトルは正規化してしまう
	dir = VNorm(dir);

	//カメラとプレイヤーの距離が一定距離離れた
	if (len > MAX_LEN_NEAR)
	{
		//本来の到達地点を計算
		dir = VScale(dir, MAX_LEN_NEAR);
		VECTOR tempPos = VAdd(_focus, dir);
		//現在のカメラ位置から上記到達地点までの方向ベクトルを計算
		VECTOR tempDir = VSub(tempPos, m_pos);
		tempDir.y = 0.0f;			//高さは無視
		tempDir = VNorm(tempDir);	//方向ベクトルなので正規化

		//目標到達地点に向けて、カメラの座標を移動させる
		tempDir = VScale(tempDir, CAMERA_MOVE_SPEED);		//カメラの速度を計算
		m_pos = VAdd(m_pos, tempDir);

		//離れてはいけない距離以上離れていた場合の処理================
		//新しく計算した位置と、注視点までの距離を計算
		tempDir = VSub(m_pos, _focus);
		tempDir.y = 0.0f;	//やっぱり高さは無視

		//離れてはいけない距離を超えたかチェック(計算量を減らすため、2乗した値で比較)
		if (VSquareSize(tempDir) > MAX_LEN_FAR * MAX_LEN_FAR)
		{
			//再度正規化し、強制的に最大距離に変更
			tempDir = VNorm(tempDir);
			tempDir = VScale(tempDir, MAX_LEN_FAR);
			m_pos = VAdd(_focus, tempDir);
		}
		//==========================================================
	}
	//カメラとプレイヤーの距離が一定以上近づいた
	else if (len < MIN_LEN_NEAR)
	{
		//本来の到達地点を計算
		dir = VScale(dir, MIN_LEN_NEAR);
		VECTOR tempPos = VAdd(_focus, dir);
		//現在のカメラ位置から上記到達地点までの方向ベクトルを計算
		VECTOR tempDir = VSub(tempPos, m_pos);
		tempDir.y = 0.0f;			//高さは無視
		tempDir = VNorm(tempDir);	//方向ベクトルを正規化

		//目標到達地点に向けて、カメラの座標を移動させる
		tempDir = VScale(tempDir, CAMERA_MOVE_SPEED);	//カメラの速度を計算
		m_pos = VAdd(m_pos, tempDir);

		//近づいてはいけない距離以上近づいた場合の処理================
		//新しく計算した位置と、注視点までの距離を計算
		tempDir = VSub(m_pos, _focus);
		tempDir.y = 0.0f;	//やっぱり高さは無視

		//近づいてはいけない距離を超えたかチェック(計算量を減らすため、2条した値で比較)
		if (VSquareSize(tempDir) < MIN_LEN_FAR * MIN_LEN_FAR)
		{
			//再度正規化し、強制的に最大距離に変更
			tempDir = VNorm(tempDir);
			tempDir = VScale(tempDir, MIN_LEN_FAR);
			m_pos = VAdd(_focus, tempDir);
		}
	}
	//------------------------------------------------------------------

	//最後に共通部分の処理
	//注視点はプレイヤーの上半身辺り
	m_focusPos = _focus;
	m_focusPos.y += TARGET_OFFSET_Y;
	//視点は見下ろし型になるように、少し上に
	m_pos.y = m_focusPos.y + CAMERA_OFFSET_Y;

	//プレイヤーの移動処理の関係でカメラの角度を使っているので
	//カメラの方向ベクトルを基にY軸回転角度を計算
	dir = VSub(m_pos, m_focusPos);
	m_rot.y = atan2f(dir.x, dir.z);

}

