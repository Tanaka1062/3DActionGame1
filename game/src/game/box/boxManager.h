#pragma once
#include <iostream>
#include <list>
#include "box.h"

using namespace std;

//箱のマネージャー
class CBoxManager
{
private:
	list<CBox*> m_box;		//箱
public:
	//コンストラクタ・デストラクタ
	CBoxManager();
	~CBoxManager();

	//初期化
	void Init();
	//モデルロード
	void Load();
	//毎フレームする処理
	void Update();
	//モデル描写
	void Draw();
	//終了処理
	void Exit();

	//箱を取得する
	CBox* GetBox(int _num);

	//箱の数を取得する
	int GetNum() { return m_box.size(); }
};

