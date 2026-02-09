#pragma once

//イベントのタイプ
enum tagEventType
{
	EVENT_TYPE_NONE = -1,	//イベントタイプなし
	EVENT_ITEM_TYPE,		//イベントアイテムタイプ

	EVENT_TYPE_NUM,			//タイプの数
};

class CEventBase
{
private:
	int m_timeCount;		//制限時間
	bool m_isActive;		//生存フラグ
	tagEventType m_type;	//タイプ

public:
	//コンストラクタ・デストラクタ
	CEventBase();
	virtual ~CEventBase();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();

	//終了処理
	virtual void Exit();

	//生存フラグを取得
	bool GetIsActive() { return m_isActive; }

	//タイプを取得
	tagEventType GetType() { return m_type; }
};

