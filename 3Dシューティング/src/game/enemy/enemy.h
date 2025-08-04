#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"

class CEnemy:public CObject
{
private:

	int m_effectId;			//エフェクトのID
	float m_radius;			//半径
	bool m_isActive;		//生存フラグ

public:
	//コンストラクタ・デストラクタ
	CEnemy();
	~CEnemy();


	//初期化
	void Init();
	//ロード
	void Load(int orginHndl,int effekctId);
	//毎フレームする処理
	void Step();
	//描写
	void Draw();

	//当たり判定後の処理
	void HitCalc();


	//弾をリクエスト
	//_pos  :どこから発射されるか
	//_speed:どの方向に進むか
	//return:生成成功か失敗か
	bool Request(const VECTOR& _pos,const VECTOR& _speed);

	//生存フラグをセット
	void SetIsActive(bool _isActive) { m_isActive = _isActive; }

	//生存フラグを取得
	bool GetIsActive() { return m_isActive; }

	//半径を取得
	float GetRadius() { return m_radius; }

	//座標を取得
	VECTOR GetPos() { return m_pos; }

private:
	//移動
	void Move();

};

