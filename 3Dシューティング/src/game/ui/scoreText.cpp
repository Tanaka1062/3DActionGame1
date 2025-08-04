#include"scoreText.h"
#include"../../lib/number/number.h"

//定義関連----------------------
static const char SCORE_GRAPHIC_PATH[] = "data/graphic/game/score.png";	//スコア文字のハンドルパス
static const int SCORE_MAX = 999;
//------------------------------

//--------------------
//	コンストラクタ
//--------------------
CScoreText::CScoreText()
{
	Init();
}
//--------------------
//	デストラクタ
//--------------------
CScoreText::~CScoreText()
{
	Exit();
}

//--------------------
//	初期化
//--------------------
void CScoreText::Init()
{
	C2DUi::Init(VGet(128.0f, 64.0f, 0.0));
	m_scoreCount = 0;

}

//--------------------
//	画像ロード
//--------------------
void CScoreText::Load()
{
	LoadGraphic(m_hndl, SCORE_GRAPHIC_PATH);
}

//--------------------
//	毎フレームする処理
//--------------------
void CScoreText::Step(int _score)
{
	//表示スコアを現在のスコアを合わせる
	if (m_scoreCount < _score)
	{
		m_scoreCount++;
	}
	
	//上限を超えないようにする
	if (m_scoreCount >= SCORE_MAX)
	{
		m_scoreCount = SCORE_MAX;
	}

}

//--------------------
//	画像描写
//--------------------
void CScoreText::Draw()
{
	C2DUi::Draw();

	//数字をそれぞれの桁に分ける
	int hundred = m_scoreCount / 100;
	int ten = (m_scoreCount / 10) % 10;
	int one = m_scoreCount % 10;

	//数字の座標
	int numPosX = static_cast<int>(m_pos.x + 120.0f);
	int numPosY = static_cast<int>(m_pos.y);

	CNumber::RequestNumber(numPosX, numPosY, hundred, 1.0f);
	CNumber::RequestNumber(numPosX + 40, numPosY, ten, 1.0f);
	CNumber::RequestNumber(numPosX + (40 * 2), numPosY, one, 1.0f);

}
