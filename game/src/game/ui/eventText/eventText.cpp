#include "eventText.h"
#include "../../data.h"

constexpr const char*	TEXT_GRAPHIC_PATH[CEventManager::EVENT_NUM] =		//背景の画像パス
{
	"data/graphic/ui/bombPartyText.png",
	"data/graphic/ui/coinPartyText.png",

};
constexpr int			ACTIVE_TIME = 300;										//表示する時間
constexpr VECTOR		TEXT_POS = { WINDOW_SIZE_HALF_X,100.0f,0.0f };			//テキストの座標

//-----------------------
//	  コンストラクタ
//-----------------------
CEventText::CEventText()
{
	Init();
}

//-----------------------
//	    デストラクタ
//-----------------------
CEventText::~CEventText()
{

}

//-----------------------
//		 初期化
//-----------------------
void CEventText::Init()
{
	C2DObject::Init();
	for (int event_i = 0; event_i < CEventManager::EVENT_NUM; event_i++)
	{
		m_textHndl[event_i] = -1;
	}
	m_pos = TEXT_POS;
}

//-----------------------
//		画像ロード
//-----------------------
void CEventText::Load()
{
	for (int event_i = 0; event_i < CEventManager::EVENT_NUM; event_i++)
	{
		if (m_textHndl[event_i] == -1)
		{
			m_textHndl[event_i] = LoadGraph(TEXT_GRAPHIC_PATH[event_i]);
		}
	}
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CEventText::Step(CEventManager::tagEventName _nowEvent)
{
	if (_nowEvent != CEventManager::EVENT_NONE)
	{
		SetHndl(m_textHndl[_nowEvent]);
		m_activeTime++;
		if (m_activeTime >= ACTIVE_TIME)
		{
			SetHndl(-1);
		}
	}
	else
	{
		m_activeTime = 0;
		SetHndl(-1);
	}
}

//-----------------------
//		 終了処理
//-----------------------
void CEventText::Exit()
{
	C2DObject::Exit();

	for (int event_i = 0; event_i < CEventManager::EVENT_NUM; event_i++)
	{
		if (m_textHndl[event_i] != -1)
		{
			DeleteGraph(m_textHndl[event_i]);
			m_textHndl[event_i] = -1;
		}
	}
}

