#pragma once

#include<DxLib.h>
#include "shot.h"
#include <vector>

using namespace std;

class CShotManager
{
private:
	vector<CShot> m_playerShot;		//プレイヤーの弾

public:
	//コンストラクタ
	CShotManager();


	//初期化
	void Init();
	//ロード
	void Load();
	//毎フレームする処理
	void Step();
	//描写
	void Draw();
	//終了処理
	void Exit();


	//座標更新
	void Update();

	//弾をリクエスト
	//_pos  :どこから発射されるか
	//_speed:どの方向に進むか
	//return:生成成功か失敗か
	void RequestPlayerShot(const VECTOR& _pos, const VECTOR& _speed);

	//弾1発分の情報取得
	CShot& GetShot(int _id) { return m_playerShot[_id]; }

	//弾の数を取得
	int GetNum() { return static_cast<int>(m_playerShot.size()); }
};


