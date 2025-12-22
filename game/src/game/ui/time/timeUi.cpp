#include "timeUi.h"
#include "../../data.h"
#include "../../lib/number.h"

static const char GRAPHIC_PATH[] =
 "data/graphic/ui/division.png" ;				//ロードするファイル名

constexpr int POS_X = WINDOW_SIZE_X / 2;
constexpr int POS_Y = 100;

CTimeUi::CTimeUi()
{
	Init();
}

CTimeUi::~CTimeUi()
{
	Exit();
}

//初期化
void CTimeUi::Init()
{
	m_oneM = 0;
	m_tenS = 0;
	m_oneS = 0;

	VECTOR pos = ZERO;

	pos.x = static_cast<float>(POS_X - NUM_SIZE / 2);
	pos.y = static_cast<float>(POS_Y);

	m_division.Init(pos);
}

//画像ロード
void CTimeUi::Load()
{
	m_division.Load(GRAPHIC_PATH);
}

//毎フレームする処理
void CTimeUi::Step(int _time)
{

	m_oneM = _time / 60;
	m_tenS = (_time % 60) / 10;
	m_oneS = (_time % 60) % 10;

}

//描画処理
void CTimeUi::Draw()
{
	CNumber::RequestNumber(POS_X - NUM_SIZE, POS_Y,m_oneM,1.0f);
	m_division.Draw();
	CNumber::RequestNumber(POS_X + NUM_SIZE / 8, POS_Y, m_tenS, 1.0f);
	CNumber::RequestNumber(POS_X + NUM_SIZE, POS_Y, m_oneS, 1.0f);

}

//終了処理
void CTimeUi::Exit()
{
	m_division.Exit();
}
