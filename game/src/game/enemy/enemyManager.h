#pragma once
#include "../character/characterBase.h"
#include <iostream>
#include <vector>

using namespace std;

//エネミーマネージャーのクラス
class CEnemyManager
{
private:
	vector<CCharacterBase*> m_enemy;			//敵のクラス

public:
	//コンストラクタ・デストラクタ
	CEnemyManager();
	~CEnemyManager();

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

