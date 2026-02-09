#include "countDown.h"
#include "../../data.h"

static 	const char* GRAPHIC_PATH[CCountDown::COUNT_NUM] =		//画像のパス
{
	"data/graphic/ui/countDown0.png",
	"data/graphic/ui/countDown1.png",
	"data/graphic/ui/countDown2.png",
	"data/graphic/ui/countDown3.png",
};

constexpr int COUNT_DOWN_TIME = 60;								//カウントダウンが変わるまでの時間

//-----------------------
//	  コンストラクタ
//-----------------------
CCountDown::CCountDown()
{
	Init();
}

//-----------------------
//	   デストラクタ
//-----------------------
CCountDown::~CCountDown()
{
	Exit();
}

//-----------------------
//		  初期化
//-----------------------
void CCountDown::Init()
{
	C2DUi::Init();
	m_pos.x = WINDOW_SIZE_X / 2.0f;
	m_pos.y = WINDOW_SIZE_Y / 2.0f;
	m_isActive = false;
	m_count = COUNT_3;
	m_timeCount = 0;
	
	for (int count_i = 0; count_i < COUNT_NUM; count_i++)
	{
		m_countHndl[count_i] = -1;
	}

	m_isEnd = false;
}

//-----------------------
//		画像ロード
//-----------------------
void CCountDown::Load()
{
	for (int count_i = 0; count_i < COUNT_NUM; count_i++)
	{
		if (m_countHndl[count_i] == -1)
		{
			m_countHndl[count_i] = LoadGraph(GRAPHIC_PATH[count_i]);
		}
	}
}

//-----------------------
//	毎フレームする処理
//-----------------------
void CCountDown::Step(bool _isCountStart)
{
	//条件が揃うとカウントが始まる
	if (_isCountStart == true)
	{
		m_isActive = true;
		m_timeCount++;
		//一定時間を経過するとカウントが進む
		if (m_timeCount >= COUNT_DOWN_TIME)
		{
			m_timeCount = 0;
			m_count--;
		}
	}
	//条件が揃ってない時は初期化する
	else
	{
		m_isActive = false;
		m_timeCount = 0;
		m_count = COUNT_3;
	}

	//カウントが0になったら終了フラグをtrueにする
	if (m_count < COUNT_0)
	{
		m_isEnd = true;
	}
}

//-----------------------
//		 画像描写
//-----------------------
void CCountDown::Draw()
{
	if (m_isActive == false)return;

	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, m_rot, m_countHndl[m_count], TRUE);
}

//-----------------------
//		 終了処理
//-----------------------
void CCountDown::Exit()
{
	//画像を破棄
	for (int count_i = 0; count_i < COUNT_NUM; count_i++)
	{
		if(m_countHndl[count_i] != -1)
		{
			DeleteGraph(m_countHndl[count_i]);
			m_countHndl[count_i] = -1;
		}
	}
}

