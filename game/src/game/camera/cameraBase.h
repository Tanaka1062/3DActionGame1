#pragma once
#include <DxLib.h>
#include "../map/mapBase.h"

//カメラのベースクラス
class CCameraBase
{
protected:
	VECTOR m_pos;		// カメラの位置
	VECTOR m_speed;		//カメラの加速度
	VECTOR m_rot;		//カメラの回転値
	VECTOR m_upVec;		// カメラ上方向
	VECTOR m_focusPos;	//カメラの注視点

public:
	//コンストラクタ・デストラクタ
	CCameraBase();
	virtual ~CCameraBase();

	//初期化
	virtual void Init(CMapBase* _map);

	//毎フレームする処理
	//_focus	:	カメラの座標
	virtual void Step(VECTOR _pos);

	//カメラの更新
	virtual void Update();

	//カメラの終了処理
	virtual void Exit();

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

	//カメラの注視点を取得
	VECTOR GetFocusPos() { return m_focusPos; }

protected:
	//座標に速度を加算する
	void UpdataSpeed();
};

