#pragma once
#include "../../lib/2DUi/2DUi.h"
#include <DxLib.h>


class CGetCoinUi
{
private:
	VECTOR m_pos;
	C2DUi m_coinUi;

public:
	CGetCoinUi();
	~CGetCoinUi();

	//初期化
	void Init();
	//ロード
	void Load();
	//毎フレームする処理
	void Step();
	//描写
	void Draw();
	//破棄
	void Exit();

};

