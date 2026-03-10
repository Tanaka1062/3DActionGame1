#pragma once
#include<DxLib.h>
#include "../../mapBase.h"

class CGrassland :public CMapBase
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

private:
	//ステージの移動処理
	void StageMove();

	//ステージの揺れる処理
	void StageShake();
};

