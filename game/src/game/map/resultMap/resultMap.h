#pragma once
#include<DxLib.h>
#include "../mapBase.h"

class CResultMap : public CMapBase
{
private:
	std::vector<bool>	m_isPodiumMoveEnd;		//表彰台が動き終わったか
	bool				m_isPodiumAllMoveEnd;	//表彰台が全て動き終わったか

public:
	//コンストラクタ
	CResultMap();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

	//表彰台が全て動き終わったかを取得
	bool GetIsPodiumAllMoveEnd() { return m_isPodiumAllMoveEnd; }
};

