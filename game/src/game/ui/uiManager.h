#pragma once
#include "../../lib/2DUi/2DUi.h"
#include <iostream>
#include <vector>

using namespace std;

class CUiManager
{
private:
	vector<C2DUi*> m_ui;		//UI
public:
	//コンストラクタ・デストラクタ
	CUiManager();
	~CUiManager();

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

