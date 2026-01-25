#pragma once
#include "moveBlock.h"

class CGimmickManager
{
private:
	CMoveBlock m_moveBlock;
public:
	CGimmickManager();
	~CGimmickManager();

	//初期化
	void Init();
	//オブジェクトのロード
	void Load();
	//毎フレームする処理
	void Step();
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

};

