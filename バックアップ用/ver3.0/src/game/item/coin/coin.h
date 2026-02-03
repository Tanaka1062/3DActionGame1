#pragma once
#include "../itemBase.h"

class CCoin : public CItemBase
{
private:
	MATRIX m_mat;		//全体の情報を持っている行列
public:
	CCoin();
	~CCoin();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();

	//数値の更新
	virtual void Update();

	//モデルの描写
	void Draw(int _sharedModel);

	//当たった時の処理
	//_name		:どのプレイヤーが触れたかを取得
	void HitCalc(CObject* _hitObject);
	
	//コインの消失
	void Delete();

};

