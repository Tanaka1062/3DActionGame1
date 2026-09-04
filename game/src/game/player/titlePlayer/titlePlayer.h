#pragma once
#include "../player.h"
#include"../../../lib/input/controllerManager.h"

//プレイヤークラス
class CTitlePlayer:public CPlayer 
{
private:
	bool m_isWin;			//勝利したかどうか
public:
	//コンストラクタ・デストラクタ
	CTitlePlayer();
	~CTitlePlayer();

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

	//勝利しているかを取得
	bool GetIsWin() { return m_isWin; }

	//勝利しているかを設定
	void SetIsWin(bool _win) { m_isWin = _win; }

private:

};

