#pragma once
#include<DxLib.h>
#include "../mapBase.h"

class CResultMap : public CMapBase
{
private:
	bool m_isPodiumMoveEnd;		//表彰台が動き終わったか
public:
	//コンストラクタ
	CResultMap();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

	//表彰台が動き終わったかを取得
	bool GetIsPodiumMoveEnd() { return m_isPodiumMoveEnd; }
};

