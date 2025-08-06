#pragma once
#include<DxLib.h>

//3Dオブジェクトの基底クラス
class CObject{
protected:
	VECTOR m_pos;			//座標
	VECTOR m_rot;			//回転角度
	VECTOR m_scale;			//拡大縮小率
	VECTOR m_speed;			//スピード
	int m_hndl;				//オブジェクトのハンドル

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

	//取得・設定---------------------
	//座標を取得
	VECTOR GetPos() { return m_pos; }

	//回転角度を取得
	VECTOR GetRot() { return m_rot; }

	//-------------------------------
};