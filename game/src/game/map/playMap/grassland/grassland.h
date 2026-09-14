#pragma once
#include<DxLib.h>
#include "../playMapBase.h"

class CGrassland :public CPlayMapBase
{
private:
	bool m_isStageFall;		//ステージが落下するかどうか
	bool m_isStageShake;	//ステージが移動しているかどうか
public:
	//コンストラクタ
	CGrassland();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

};

