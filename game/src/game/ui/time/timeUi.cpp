#include "timeUi.h"
#include "../../data.h"
#include "../../lib/number.h"

constexpr const char GRAPHIC_PATH[] =
 "data/graphic/ui/division.png" ;				//ロードするファイル名

static const VECTOR POS = {static_cast<float>(WINDOW_SIZE_X / 2.0f),100.0f,0.0f};

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

	VECTOR pos = POS;

	pos.x = POS.x - NUM_SIZE / 2;

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
	CNumber::RequestNumber(POS.x - NUM_SIZE, POS.y,m_oneM,1.0f);
	m_division.Draw();
	CNumber::RequestNumber(POS.x + NUM_SIZE / 8, POS.y, m_tenS, 1.0f);
	CNumber::RequestNumber(POS.x + NUM_SIZE, POS.y, m_oneS, 1.0f);

}

//終了処理
void CTimeUi::Exit()
{
	m_division.Exit();
}
