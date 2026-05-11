#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <vector>

class CResultManager
{
private:
	std::vector<C2DObject*>m_ui;		//UI
public:
	//コンストラクタ・デストラクタ
	CResultManager();
	~CResultManager();

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

