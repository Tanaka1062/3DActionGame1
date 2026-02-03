#pragma once
#include "gimmickBase.h"
#include <iostream>
#include <vector>

class CGimmickManager
{
private:
	std::vector<CGimmickBase*> m_gimmick;
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

	//ギミックの数を取得
	int GetGimmickNum() { return static_cast<int>(m_gimmick.size()); }

	//ギミックを取得
	CGimmickBase* GetGimmick(int _num) { return m_gimmick[_num]; }
};

