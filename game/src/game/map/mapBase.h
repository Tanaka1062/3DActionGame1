#pragma once
#include<DxLib.h>
#include "../../lib/model/actor.h"
#include <iostream>
#include <vector>

class CMapBase
{
public:
	struct tagStageSpawnData							//ステージのスポーン情報
	{
		int							mapItemFrameNum;	//マップ全体のアイテムのフレームの数
		int							mapItemSpawnNum;	//マップ全体のアイテムの出現座標の数
		int							itemFrameNum;		//アイテムフレームの数
		int							itemSpawnNum;		//アイテムスポーンの数
		int							coinFrameNum;		//コインフレームの数
		int							coinSpawnNum;		//コインスポーンの数
	};
protected:
	int										m_mapId;			//マップのID
	std::vector<std::unique_ptr<CActor>>	m_stage;			//ステージ
	int										m_stageId;			//ステージのID
	int										m_mapMoveTimer;		//マップの移動する時間
	std::vector<tagStageSpawnData>			m_stageSpawnData;	//ステージのスポーンデータ
	std::vector<std::unique_ptr<CObject>>	m_object;			//ステージのオブジェクト
public:
	//コンストラクタ・デストラクタ
	CMapBase();
	virtual~CMapBase();

	//初期化
	virtual void Init(int _mapId = -1);

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

	//ステージを取得
	CObject* GetStage(int _num) { return m_stage[_num].get(); }

	//マップIDを取得
	int GetMapId() { return m_mapId; }

	//ステージの数を取得
	int GetStageNum() { return static_cast<int>(m_stage.size()); }

	//現在のステージIDを取得
	int GetStageId() { return m_stageId; }

	//ステージのスポーンデータ取得
	tagStageSpawnData GetStageSpawnData(int _num) { return m_stageSpawnData[_num]; }

	//オブジェクトを取得
	CObject* GetStageObject(int _num) { return m_object[_num].get(); }

	//オブジェクトの数を取得
	int GetStageObjectNum() { return static_cast<int>(m_object.size()); }
};

