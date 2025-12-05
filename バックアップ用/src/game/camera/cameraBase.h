#pragma once
#include <DxLib.h>

//カメラのベースクラス
class CCameraBase
{
protected:
	VECTOR m_pos;		// カメラの位置
	VECTOR m_rot;		//カメラの回転値
	VECTOR m_upVec;		// カメラ上方向

public:
	//コンストラクタ
	CCameraBase();

	//初期化
	virtual void Init(VECTOR _focus);

	//毎フレームする処理
	//_focus	:	プレイヤーの座標
	//_rot		:	プレイヤーの回転角度
	virtual void Step(VECTOR _focus, float _rot);

	//カメラの更新
	virtual void Update();

	//カメラの座標取得
	VECTOR GetPos() { return m_pos; }
	//カメラの座標設定
	void SetPos(VECTOR _pos) { m_pos = _pos; }

	//角度を取得
	VECTOR GetRot() { return m_rot; }
	//角度を設定
	void SetRot(VECTOR _rot) { m_rot = _rot; }

	//カメラの上方向を取得
	VECTOR GetUp() { return m_upVec; }


};

