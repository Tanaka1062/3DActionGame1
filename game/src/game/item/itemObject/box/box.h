#pragma once
#include "../itemObjectBase.h"

class CBox : public CItemObjectBase
{
private:
	int m_spawnTime;		//時間カウント
	VECTOR m_spawnPos;		//出現座標

public:
	CBox();

	//初期化
	void Init();

	//毎フレームする処理
	void Step();

	//出現座標をセット
	void SetSpawnPos(VECTOR _pos) { m_spawnPos = _pos; }

private:

	//スポーン処理
	void Spawn();

};

