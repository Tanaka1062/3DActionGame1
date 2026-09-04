#include "titlePlayer.h"
#include "../../data.h"
#include "../../../lib/myMath/myMath.h"
#include <math.h>

//定義関連---------------------------

//プレイヤー関連--------------------------------
constexpr float SHADOW_SIZE = 0.0f;						//丸影の大きさ
//----------------------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CTitlePlayer::CTitlePlayer()
{
	CCharacterBase::Init();
}

//-----------------------
//	デストラクタ
//-----------------------
CTitlePlayer::~CTitlePlayer()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CTitlePlayer::Init(tagPlayerName _name, tagPadName _padName)
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
}

//-----------------------
//	モデルロード
//-----------------------
void CTitlePlayer::Load(int _modelHndl)
{
	CObject::DuplicateModel(_modelHndl);
	m_shadow.Load();
}

//-----------------------
//毎フレームする処理
//-----------------------
void CTitlePlayer::Step()
{
	if (m_isActive == false)return;

	//最初はデフォルト
	tagAnim animId = ANIMID_DEFAULT;

	//名前によってアニメーションを変える
	switch (m_name)
	{
	case PLAYER_1:
		animId = ANIMID_TITLE_POSE1;
		break;
	case PLAYER_2:
		animId = ANIMID_TITLE_POSE2;
		break;
	case PLAYER_3:
		animId = ANIMID_TITLE_POSE3;
		break;
	case PLAYER_4:
		animId = ANIMID_TITLE_POSE4;
		break;
	}

	//アニメーション再生
	RequestAnim(animId, 0.5f, true);
}

//-----------------------
//		描写処理
//-----------------------
void CTitlePlayer::Draw()
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
//		更新処理
//-----------------------
void CTitlePlayer::Update()
{
	CCharacterBase::Update();
}

//終了処理
void CTitlePlayer::Exit()
{
	CCharacterBase::Exit();
}

