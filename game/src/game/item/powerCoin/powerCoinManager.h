#pragma once
#include "powerCoin.h"
#include <iterator>
#include<vector>
#include "../../player/playerManager.h"

using namespace std;

enum tagPowerCoinName
{
	COIN_RED,			//赤コイン
	COIN_GREEN,			//緑コイン
	COIN_BLUE,			//青コイン
		
	COIN_NUM,			//コインの数
};

enum tagPowerCoinPos
{
	COIN_SPAWN_POS_1,			//コインの出現座標１
	COIN_SPAWN_POS_2,			//コインの出現座標２
	COIN_SPAWN_POS_3,			//コインの出現座標３
	COIN_SPAWN_POS_4,			//コインの出現座標４

	COIN_SPAWN_POS_NUM,			//コインの出現座標の数
};

class CPowerCoinManager
{
private:
	vector<CPowerCoin*>m_powerCoin;			//パワーコイン
	int m_timeCount;						//時間カウント
	VECTOR m_spawnPos[COIN_SPAWN_POS_NUM];	//コインの出現座標
	CPlayerManager* m_playerManager;		//プレイヤーのマネージャークラス
public:
	CPowerCoinManager();
	~CPowerCoinManager();

	//初期化
	void Init(CPlayerManager* _playerManager);
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

	//パワーコインを取得
	CPowerCoin* GetPowerCoin(int _num) { return m_powerCoin[_num]; }

	//パワーコインの数を取得
	int GetPowerCoinNum() { return static_cast<int>(m_powerCoin.size()); }

private:
	//コインを出現させる
	void SpawnCoin();
};

