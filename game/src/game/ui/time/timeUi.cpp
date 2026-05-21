#include "timeUi.h"
#include "../../data.h"
#include "../../system/number/number.h"

static const char GRAPHIC_PATH[] =
 "data/graphic/ui/division.png" ;				//ロードするファイル名

constexpr VECTOR INIT_POS =						//初期座標	
{ WINDOW_SIZE_HALF_X,100.0f,0.0f };				
constexpr int SECOND_DIGIT = 2;					//秒の桁数

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
	m_minute = 0;
	m_second = 0;

	VECTOR pos = ZERO;

	pos.x = INIT_POS.x - static_cast<float>(CNumber::NUM_SIZE) * 0.5f;
	pos.y = INIT_POS.y;

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

	m_minute = _time / 60;
	m_second = _time - (m_minute * 60);

}

//描画処理
void CTimeUi::Draw()
{
	//分を表示
	CNumber::RequestNumber(INIT_POS.x - static_cast<float>(CNumber::NUM_SIZE),INIT_POS.y,m_minute);
	m_division.Draw();
	//秒を表示
	CNumber::RequestNumber(INIT_POS.x + static_cast<float>(CNumber::NUM_SIZE / 8), INIT_POS.y, m_second,1.0f, SECOND_DIGIT);

}

//終了処理
void CTimeUi::Exit()
{
	m_division.Exit();
}
