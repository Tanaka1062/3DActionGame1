#pragma once
#include<DxLib.h>
#include "../shot/shotManager.h"
#include "../../lib/model/3DObject.h"

static const char PLAYER_MODEL_PATH[] =
{ "data/model/player/fightrJet.mv1" };				//ロードするファイル名

class CPlayer:public CObject
{
private:
	float m_radius;				//半径
	bool m_isActive;			//生存フラグ

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();


	//初期化
	void Init();
	//オブジェクトの描写
	void Draw();
	//毎フレームする処理
	void Step(CShotManager& _shot);

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
	void HitCalc();

private:
	//移動
	void Move();
	//回転
	void Rotate();
	//弾を発射
	void Shot(CShotManager& _shot);



};


