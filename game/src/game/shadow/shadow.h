#pragma once
#include"../../lib/model/3DObject.h"

//丸影のクラス
class CShadow :public CObject
{
private:
	bool m_isPosUpdate;			//座標を更新したかフラグ
public:

	//初期化
	void Init(VECTOR _pos,float _scale);
	//モデルのロード
	void Load();
	//毎フレームする処理
	void Step(VECTOR _pos);

	//更新したかを取得
	bool GetIsPosUpdate() { return m_isPosUpdate; }
	//更新したかを設定
	void SetIsPosUpdate(bool _isPosUpdate) { m_isPosUpdate = _isPosUpdate; }
};

