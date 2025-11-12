#pragma once
#include "powerCoin.h"
#include <iterator>
#include<vector>

using namespace std;

enum tagPowerCoinName
{
	COIN_RED,			//赤コイン
	COIN_GREEN,			//緑コイン
	COIN_BLUE,			//青コイン
		
	COIN_NUM,			//コインの数
};

class CPowerCoinManager
{
private:
	vector<CPowerCoin*>m_powerCoin;		//パワーコイン
public:
	CPowerCoinManager();
	~CPowerCoinManager();

	//初期化
	void Init();
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();
	//数値の更新
	void Update();
	//描写処理
	void Draw();
	//終了処理
	void Exit();

};

