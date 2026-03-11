#pragma once
#include<DxLib.h>
#include "../../lib/model/3DObject.h"
#include <iostream>
#include <vector>

class CMapBase
{
protected:
	std::vector<CObject*>			m_stage;			//ステージ
	int								m_stageId;			//ステージのID
	int								m_mapMoveTimer;		//マップの移動する時間
	struct tagStageSpawnData
	{
		int mapItemFrameNum;
		int mapItemSpawnNum;
		int itemFrameNum;
		int itemSpawnNum;
		int coinFrameNum;
		int coinSpawnNum;
	};
	std::vector<tagStageSpawnData>	m_stageSpawnData;	//ステージのスポーンデータ
	std::vector<CObject*> m_object;						//ステージのオブジェクト
public:
	//コンストラクタ・デストラクタ
	CMapBase();
	virtual~CMapBase();

	//初期化
	virtual void Init();

	//モデルロード
	virtual void Load();

	//毎フレームする処理
	virtual void Step();

	//モデル描写
	virtual void Draw();

	//更新処理
	virtual void Update();

	//終了処理
	virtual void Exit();

	//ハンドルを取得
	int GetHndl(int _num) { return m_stage[_num]->GetHndl(); }

	//ステージの生存フラグを取得
	bool GetStageActive(int _num) { return m_stage[_num]->GetActive(); }

	//ステージの座標を取得
	VECTOR GetStagePos(int _num) { return m_stage[_num]->GetPos(); }

	//ステージの数を取得
	int GetStageNum() { return static_cast<int>(m_stage.size()); }

	//現在のマップIDを取得
	int GetStageId() { return m_stageId; }

	//ステージのスポーンデータ取得
	tagStageSpawnData GetStageSpawnData(int _num) { return m_stageSpawnData[_num]; }

	//オブジェクトを取得
	CObject* GetStageObject(int _num) { return m_object[_num]; }

	//オブジェクトの数を取得
	int GetStageObjectNum() { return m_object.size(); }
};

