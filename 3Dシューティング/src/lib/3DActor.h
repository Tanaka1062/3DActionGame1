#pragma once
#include<DxLib.h>

class C3DActor
{
protected:

	VECTOR m_pos;				//座標
	VECTOR m_rot;				//回転角度
	VECTOR m_speed;				//移動速度
	VECTOR m_scale;				//大きさ
	int m_hndl;					//モデルハンドル
	float m_radius;				//半径
	bool m_isActive;			//生存フラグ

public:
	//コンストラクタ・デストラクタ
	C3DActor();
	~C3DActor();


	//初期化
	virtual void Init();
	//ロード
	virtual void Load();
	//毎フレームする処理
	virtual void Step();
	//描写
	virtual void Draw();
	//破棄
	virtual void Exit();
	//データ関連の破棄
	virtual void Delete();

	//座標,回転値更新
	virtual void Update();

	//座標出力
	VECTOR GetPos() { return m_pos; }
	//角度出力
	VECTOR GetRot() { return m_rot; }
	//半径を出力
	float GetRadius() { return m_radius; }

	//生存フラグを取得
	bool GetActive() { return m_isActive; }

	//当たり判定の座標用
	VECTOR GetCenter();

	//当たり判定後の処理
	virtual void HitCalc();

};

