#pragma once
#include "../../lib/2D/2DObject.h"
#include <iostream>
#include <array>

namespace UiTitleData
{
	enum tagUiName
	{
		UI_TITLE,			//タイトル
		UI_START_TEXT,		//スタートテキスト

		UI_NUM,				//UIの数
	};

}

class CUiTitleManager
{
private:
	std::array<std::unique_ptr<C2DObject>, UiTitleData::UI_NUM>	m_ui;		//UI
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

