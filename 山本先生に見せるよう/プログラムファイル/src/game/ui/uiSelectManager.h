#pragma once
#include "../../lib/2DUi/2DUi.h"
#include <iostream>
#include <vector>
#include "countDown/countDown.h"

class CUiSelectManager
{
private:
	std:: vector<C2DUi*>m_ui;		//UI
	CCountDown m_countDown;			//カウントダウン
public:
	//コンストラクタ・デストラクタ
	CUiSelectManager();
	~CUiSelectManager();

	void Init();
	//ロード
	void Load();
	//毎フレームする処理
	void Step(bool _allReady);
	//描写
	void Draw();
	//破棄
	void Exit();

	//カウントダウンが終了したかを取得
	bool GetCountDownEnd() { return m_countDown.GetIsEnd(); }
};

