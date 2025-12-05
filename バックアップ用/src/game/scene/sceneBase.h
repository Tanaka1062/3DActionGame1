#pragma once

//ゲーム本編を管理するクラス
class CSceneBase
{
protected:

	//シーン処理の流れ
	enum tagScene
	{
		INIT,		//データ初期化
		LOAD,		//データ読み込み
		MAIN,		//本編実行
		END,		//終了前のゲーム破棄
	};

	tagScene m_state;	//シーンの状態	

public:
	//コンストラクタ
	CSceneBase();
	//デストラクタ
	virtual ~CSceneBase();

	//実行処理
	int Loop();
	//描画処理
	virtual void Draw();

	//初期化
	virtual void Init();

	//データ読み込み
	virtual void Load();

	//メイン処理
	virtual void Step();

	//終了前処理
	virtual void Exit();

};

