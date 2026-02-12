#include "resultPlayer.h"
#include "../../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>

//定義関連---------------------------

//プレイヤー関連--------------------------------
constexpr float SHADOW_SIZE = 0.0f;						//丸影の大きさ
//----------------------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CResultPlayer::CResultPlayer()
{
	CCharacterBase::Init();
}

//-----------------------
//	デストラクタ
//-----------------------
CResultPlayer::~CResultPlayer()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CResultPlayer::Init(tagPlayerName _name, tagPadName _padName)
{
	CCharacterBase::Init();
	m_padName = _padName;
	m_name = _name;
	m_shadow.Init(m_pos, SHADOW_SIZE);
	m_objectName = OBJECT_PLAYER;
	m_isGravity = false;
	m_state = WAIT;
	m_rot.y = 90.0f * (DX_PI_F/180.0f);
	m_isWin = false;
	m_CoinNowUi.Init();
}

//-----------------------
//	モデルロード
//-----------------------
void CResultPlayer::Load(int _modelHndl)
{
	CObject::DuplicateModel(_modelHndl);
	m_shadow.Load();
	m_CoinNowUi.Load();
}

//-----------------------
//毎フレームする処理
//-----------------------
void CResultPlayer::Step()
{
	if (m_isActive == false)return;
	VECTOR uiPos = m_pos;
	uiPos.x -= 8.0f;
	uiPos.y -= 5.0f;
	m_CoinNowUi.Step(uiPos,m_rad,m_money,UI_TYPE_COIN);
	if (m_isWin == true)
	{
		CPlayer::Winner();
	}
	else
	{
		CPlayer::Clap();
	}
}

//-----------------------
//		描写処理
//-----------------------
void CResultPlayer::Draw()
{
	CCharacterBase::Draw();
	m_CoinNowUi.Draw();
#ifdef DEBUG
	//当たり判定を表示
	DrawSphere3D(GetCenter(), m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

	VECTOR attackPos;
	attackPos.x = -sinf(m_rot.y) * ATTACK_LENGTH;
	attackPos.y = GetCenter().y;
	attackPos.z = -cosf(m_rot.y) * ATTACK_LENGTH;

	attackPos = VAdd(attackPos, m_pos);

#endif // DEBUG
	
}

//-----------------------
//		更新処理
//-----------------------
void CResultPlayer::Update()
{
	CCharacterBase::Update();
	m_CoinNowUi.Update();
}

//終了処理
void CResultPlayer::Exit()
{
	CCharacterBase::Exit();
	m_CoinNowUi.Exit();
}

