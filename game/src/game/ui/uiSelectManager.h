#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <array>
#include "countDown/countDown.h"

namespace UiSelectData
{
	enum tagUiName
	{
		UI_TEXT,		//テキスト
		UI_TEXT2,		//テキスト２

		UI_NUM,			//UIの数
	};
}

class CUiSelectManager
{
private:
	std:: array<std::unique_ptr<C2DObject>,UiSelectData::UI_NUM>	m_ui;			//UI
	CCountDown														m_countDown;	//カウントダウン
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

