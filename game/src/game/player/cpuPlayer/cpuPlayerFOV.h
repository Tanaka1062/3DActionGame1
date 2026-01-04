#pragma once
#include "../../lib/model/3DObject.h"
#include <iostream>
#include<vector>

class CCpuPlayerFOV : public CObject
{
private:
	std::vector<CObject*>m_hitObject;		//接触しているオブジェクト
	std::vector<CObject*>m_objectBuf;		//オブジェクトを保存

public:
	CCpuPlayerFOV();
	~CCpuPlayerFOV();

	//初期化
	void Init();

	//毎フレームする処理
	void Step(CObject* _object);

	//当たり判定後の処理
	void HitCalc(CObject* _hitObject);

	//保存しているオブジェクトの数を取得
	int GetObjectBufNum() { return static_cast<int>(m_objectBuf.size()); }

	//保存しているオブジェクトのアドレスを取得
	CObject* GetObjectBuf(int _num) {return m_objectBuf[_num]; }

};

