#pragma once
#include<DxLib.h>

//3Dオブジェクトの基底クラス
class CObject{
protected:
	VECTOR m_pos;			//座標
	VECTOR m_speed;			//速度
	VECTOR m_rot;			//回転角度
	VECTOR m_scale;			//拡大縮小率
	int m_hndl;				//オブジェクトのハンドル
	float m_rad;			//半径
	bool m_isActive;		//生存フラグ

public:
	//コンストラクタ・デストラクタ
	CObject();
	virtual ~CObject();

	//初期化
	virtual void Init();
	//終了処理
	virtual void Exit();
	//数値の更新
	virtual void Update();
	//オブジェクトの描写
	virtual void Draw();
	//オブジェクトのロード
	virtual void Load();

	//モデルデータロード
	//_filePath		:読み込みたいモデルデータパス
	//return	true:ロード成功		false:ロード失敗
	bool LoadModel(const char* _filePath);

	//モデルコピーロード
	//_originHndl	:コピー元のモデルのハンドル
	//return	true:ロード成功		false:ロード失敗
	bool DuplicateModel(int _originHndl);
	
	//モデルデータ削除
	void DeleteModel();

	//当たり判定後の処理
	virtual void HitCalc();

	//オブジェクトを押し出す
	// _push	:押し出す力		
	void ObjPush(VECTOR _push);

	//取得・設定---------------------
	//座標を取得
	VECTOR GetPos() { return m_pos; }
	//座標を設定
	void SetPos(VECTOR _pos) { m_pos = _pos; }

	//移動後の座標を取得
	VECTOR GetMovePos() { return VAdd(GetCenter(), m_speed); }

	//速度を取得
	VECTOR GetSpeed() { return m_speed; }
	//速度を設定(floot)
	void SetSpeed(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) 
	{
		m_speed.x = _x;
		m_speed.y = _y;
		m_speed.z = _z;
	}
	//速度を設定(VECTOR)
	void SetSpeed(VECTOR _speed) { m_speed = _speed; }

	//回転角度を取得
	VECTOR GetRot() { return m_rot; }
	//回転角度を設定(float)
	void SetRot(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		m_rot.x = _x;
		m_rot.y = _y;
		m_rot.z = _z;
	}
	//回転角度を設定(VECTOR)
	void SetRot(VECTOR _rot) { m_rot = _rot; }

	//半径を取得
	float GetRad() { return m_rad; }
	//半径を設定
	void SetRad(float _rad) { m_rad = _rad; }

	//中心座標を取得
	VECTOR GetCenter();

	//生存フラグを取得
	bool GetActive() { return m_isActive; }
	//生存フラグを設定
	void SetActive(bool _isActive) { m_isActive = _isActive; }

	//ハンドルを取得
	int GetHndl() { return m_hndl; }

	//-------------------------------

protected:
	
	//速度のリセット
	void ResetSpeed();

};

