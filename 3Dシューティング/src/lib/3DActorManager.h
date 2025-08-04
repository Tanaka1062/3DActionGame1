#pragma once

#include<DxLib.h>
#include<vector>
#include "3DActor.h"
using namespace std;

//定義関連===========================
static const int ENEMY_NUM = 50;	//エネミーの数
//===================================

class C3DActorManager
{
protected:
	int m_actMax;				//アクターの最大数
	vector<C3DActor*> m_act;	//アクターの配列

public:
	////コンストラクタ
	//C3DActorManager();


	////初期化
	//virtual void Init();
	////ロード
	//void Load();
	////毎フレームする処理
	//void Step();
	////描写
	//void Draw();
	////終了処理
	//void Exit();


	////座標更新
	//void Update();

	////敵をリクエスト
	//void Request();

	////敵一体の情報取得
	//C3DActor* GetEnemy(int _id) { return m_act[_id]; }

};


