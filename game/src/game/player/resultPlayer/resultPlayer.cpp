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
//		初期化
//-----------------------
void CResultPlayer::Init(tagPlayerName _name, tagPadName _padName, int _rank)
{
	CCharacterBase::Init();
	m_padName = _padName;
	m_name = _name;
	m_shadow.Init(m_pos, SHADOW_SIZE);
	m_objectName = OBJECT_PLAYER;
	m_isGravity = false;
	m_state = WAIT;
	m_rot.y = 90.0f * (DX_PI_F/180.0f);
	m_rank = _rank;
	m_resultState = WISH;
}

//-----------------------
//	モデルロード
//-----------------------
void CResultPlayer::Load(int _modelHndl)
{
	CObject::DuplicateModel(_modelHndl);
	m_shadow.Load();
}

//-----------------------
//毎フレームする処理
//-----------------------
void CResultPlayer::Step(bool _podiumMoveEnd)
{
	if (m_isActive == false)return;
	VECTOR uiPos = m_pos;
	uiPos.x -= 8.0f;
	uiPos.y -= 5.0f;

	switch (m_resultState)
	{
	case CResultPlayer::WISH:
		Wish();
		if (_podiumMoveEnd == true)
		{
			m_resultState = POSE_IN;
		}
		break;
	case CResultPlayer::POSE_IN:
		ResultPoseIn();
		break;
	case CResultPlayer::POSE:
		ResultPose();
		break;
	}
}

//-----------------------
//		描写処理
//-----------------------
void CResultPlayer::Draw()
{
	CCharacterBase::Draw();
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
//	  願いモーション
//-----------------------
void CResultPlayer::Wish()
{
	//願いのアニメーション
	RequestAnim(ANIMID_WISH, 0.8f, true);
}

//-----------------------
// リザルト前モーション
//-----------------------
void CResultPlayer::ResultPoseIn()
{
	RequestAnim(ANIMID_RESULT_POSE1_IN + (m_rank * 2) , 0.3f);

	if (GetAnimEnd() == true)
	{
		m_resultState = POSE;
	}
}

//-----------------------
//	   勝利モーション
//-----------------------
void CResultPlayer::ResultPose()
{
	//勝利のアニメーション
	RequestAnim(ANIMID_RESULT_POSE1 + (m_rank * 2), 0.5f, true);
}

