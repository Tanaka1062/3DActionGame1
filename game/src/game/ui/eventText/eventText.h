#pragma once
#include "../../../lib/2D/2DObject.h"
#include "../../event/eventManager.h"

class CEventText :public C2DObject
{
private:
	int m_textHndl[CEventManager::EVENT_NUM];		//テキストハンドル
	int m_activeTime;								//表示時間
public:
	//コンストラクタ・デストラクタ
	CEventText();
	~CEventText();

	//初期化
	void Init();

	//画像ロード
	void Load();

	//毎フレームする処理
	void Step(CEventManager::tagEventName _nowEvent);

	//終了処理
	void Exit();

};

