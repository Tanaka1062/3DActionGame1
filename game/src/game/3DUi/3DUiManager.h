#pragma once
#include "3DUi.h"
#include <iostream>
#include <vector>

enum tag3DUiName
{
	MT_NONE = -1,		//初期化用
	MT_CROWN,			//王冠
	MT_PLAYER1_NAME,	//プレイヤー1の名前	
	MT_PLAYER2_NAME,	//プレイヤー2の名前
	MT_PLAYER3_NAME,	//プレイヤー3の名前
	MT_PLAYER4_NAME,	//プレイヤー4の名前
	MT_CPU_NAME,		//コンピュータの名前

	MT_NUM,				//ナンバーの数
};

class C3DUiManager
{
public:
	
	static C3DUiManager* m_instance;		//インスタンス

	//インスタンスの取得
	static C3DUiManager* GetInstance()		
	{
		if (m_instance == nullptr)
		{
			m_instance = new C3DUiManager;
		}

		return m_instance;
	}

	//インスタンスの削除
	static void DeleteInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

private:
	std::vector<C3DUi*> m_3DUi;
public:
	//コンストラクタ・デストラクタ
	C3DUiManager();
	~C3DUiManager();

	//初期化
	void Init();

	//描画処理
	void Draw();

	//終了処理
	void Exit();

	//ロードの呼び出し処理
	int RequsetLoad(int _3DUiId);

	//UIを取得
	C3DUi* GetUi(int _3DUiId) { return m_3DUi[_3DUiId]; }

};

