#include"score.h"
#include"../../lib/number/number.h"

//定義関連----------------------
static const char SCORE_GRAPHIC_PATH[] = "data/graphics/game/score.png";	//スコア文字のハンドルパス
//------------------------------

//--------------------
//	コンストラクタ
//--------------------
CScore::CScore()
{
	Init();
}
//--------------------
//	デストラクタ
//--------------------
CScore::~CScore()
{
	Exit();
}

//--------------------
//	初期化
//--------------------
void CScore::Init()
{
	C2DUi::Init(VGet(128.0f, 64.0f, 0.0));
	m_scoreCount = 0;
	m_scoreNow = 0;

}

//--------------------
//	画像ロード
//--------------------
void CScore::Load()
{
	LoadGraphic(m_hndl, SCORE_GRAPHIC_PATH);
}

//--------------------
//	毎フレームする処理
//--------------------
void CScore::Step()
{

}

//--------------------
//	画像描写
//--------------------
void CScore::Draw()
{
	C2DUi::Draw();

	int hundred = m_scoreCount / 100;
	int ten = (m_scoreCount / 10) % 10;
	int one = m_scoreCount % 10;

	CNumber::RequestNumber()
}
