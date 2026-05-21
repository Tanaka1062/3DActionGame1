#pragma once
#include "../../lib/2D/2DObject.h"

class CTimeUi
{
private:
	C2DObject	m_division;	//区切り
	int			m_minute;	//分
	int			m_second;	//秒
public:
	CTimeUi();
	~CTimeUi();

	//初期化
	void Init();

	//画像ロード
	void Load();

	//毎フレームする処理
	void Step(int _time);

	//描画処理
	void Draw();

	//終了処理
	void Exit();

};

