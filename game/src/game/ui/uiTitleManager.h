#pragma once
#include "../../lib/2DUi/2DUi.h"
#include <iostream>
#include <vector>

class CUiTitleManager
{
private:
	std::vector<C2DUi*>m_ui;		//UI
public:
	//コンストラクタ・デストラクタ
	CUiTitleManager();
	~CUiTitleManager();

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

