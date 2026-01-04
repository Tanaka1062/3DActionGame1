#pragma once
#include "../player.h"
#include"../../lib/input/controllerManager.h"

//プレイヤークラス
class CSelectPlayer:public CPlayer 
{
private:

public:
	//コンストラクタ・デストラクタ
	CSelectPlayer();
	~CSelectPlayer();

	//初期化
	void Init(tagPlayerName _name, tagPadName _padName);

	//モデルロード
	void Load(int _modelHndl);

	//毎フレームする処理
	void Step();

	//描写処理
	void Draw();

	//更新処理
	void Update();

	//終了処理
	void Exit();

private:

};

