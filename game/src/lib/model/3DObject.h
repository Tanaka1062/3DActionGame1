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

	//移動後の座標を取得
	VECTOR GetMovePos() { return VAdd(GetCenter(), m_speed); }

	//速度を取得
	VECTOR GetSpeed() { return m_speed; }

	//回転角度を取得
	VECTOR GetRot() { return m_rot; }

	//半径を取得
	float GetRad() { return m_rad; }

	//中心座標を取得
	VECTOR GetCenter();

	//生存フラグを取得
	bool GetActive() { return m_isActive; }

	//-------------------------------
};

