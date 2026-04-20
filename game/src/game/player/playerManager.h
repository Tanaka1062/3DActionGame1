#pragma once
#include <iostream>
#include <vector>
#include "player.h"
#include"cpuPlayer/cpuPlayerFOV.h"
#include "../map/mapManager.h"
#include "../3DUi/3DUiManager.h"

//エネミーマネージャーのクラス
class CPlayerManager
{
private:
	std::vector<CPlayer*>				m_player;					//プレイヤーのクラス
	std::vector <int>					m_modelHndl;				//モデルのハンドル
	std::vector<int>					m_materialHndl;				//マテリアルのハンドル
	std::vector <std::vector<VECTOR>>	m_spawnPos;					//プレイヤーの出現座標
	std::vector<CCpuPlayerFOV*>			m_cpuFOV;					//CPUの視界範囲クラス
	int									m_crownId;					//王冠のUiId
	struct tagName													//プレイヤーの名前
	{
		int								m_UiId;						//プレイヤーの名前UiId
		int								m_activeTime;				//生存時間
	};
	tagName								m_playerName[PLAYER_NUM];	//プレイヤーの名前UI

public:
	//コンストラクタ・デストラクタ
	CPlayerManager();
	~CPlayerManager();

	//初期化
	void Init();
	//オブジェクトのロード
	void Load(CMapBase* _map,C3DUiManager* _3DUiManager);
	//毎フレームする処理
	void Step(CAttackManager* _attackManager,CShotManager* _shotManager, C3DUiManager* _3DUiManager,float _rot,int _stageId);
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

	//プレイヤーの数を取得
	int GetPlayerNum() { return static_cast<int>(m_player.size()); }

	//プレイヤーを取得
	CPlayer* GetPlayer(int _num) { return m_player[_num]; }

	//CPUの視界範囲の数を取得
	int GetCpuPlayerFOVNum() { return static_cast<int>(m_cpuFOV.size()); }

	//CPUの視界範囲を取得
	CCpuPlayerFOV* GetCpuPlayerFOV(int _num) { return m_cpuFOV[_num]; }

	//ゲームが終わったかを取得
	bool GetIsEnd();

};

