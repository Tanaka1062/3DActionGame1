#include "coin.h"
#include "../../lib/myMath/myMath.h"

static const float DROP_SPEED = 14.0f;			//飛ぶスピード
static const float DROP_JUMP = 7.0f;			//上に飛ぶ力
static const float ROT_SPEED = 0.05f;			//回転速度
static const int ADD_MONEY = 1;					//増えるお金の量

CCoin::CCoin()
{
	m_state = ITEM_WAIT;
	m_playerName = PLAYER_NONE;
}

CCoin::~CCoin()
{
	
}

//---------------------
//		 初期化
//---------------------
void CCoin::Init()
{
	CItemBase::Init();

	m_playerName = PLAYER_NONE;

	m_isActive = false;
	m_itemType = ITEM_TYPE_COIN;
	m_isPushed = false;

}

//---------------------
// 毎フレームする処理
//---------------------
void CCoin::Step()
{
	//少しずつ回転させる
	m_rot.y += ROT_SPEED;

	//コインを飛ばす
	if (m_state == ITEM_FLYING)
	{
		m_speed.x *= 0.9f;
		m_speed.z *= 0.9f;

		VECTOR speed = m_speed;

		speed.y = 0.0f;

		float speedLen = VSize(speed);

		if (speedLen <= 0.1f)
		{
			m_speed.x = 0.0f;
			m_speed.z = 0.0f;
			m_state = ITEM_WAIT;
		}
	}

	CItemBase::Step();
}

//---------------------
//		数値の更新
//---------------------
void CCoin::Update()
{
	CItemBase::Update();

}

//---------------------
//	当たった時の処理
//---------------------
void CCoin::HitCalc(CObject* _hitObject)
{
	//_hitObjectがnullだったら処理をしない
	if (_hitObject == nullptr)return;

	//プレイヤーの場合の処理----------------------------------
	if (_hitObject->GetObjectType() == OBJECT_PLAYER)
	{
		//飛んでいる場合は処理をしない
		if (m_state == ITEM_FLYING)return;

		//プレイヤーデータ保存用
		CPlayer* player = nullptr;

		//プレイヤークラスにダウンキャストする
		player = dynamic_cast<CPlayer*>(_hitObject);

		//プレイヤーをパワーアップさせる
		player->AddMoney(ADD_MONEY);

		m_isActive = false;
		m_playerName = player->GetPlayerName();
		m_owner = player;
	}
	//--------------------------------------------------------

}

//---------------------
//	コインのドロップ
//---------------------
void CCoin::Drop(VECTOR _pos, float _rotY)
{
	//角度ゼロで進む速度
	VECTOR defaultDir = { 0.0f,DROP_JUMP,DROP_SPEED };
	//上記を行列に変換する
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(_rotY);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

	m_pos = _pos;
	m_state = ITEM_FLYING;
	m_isActive = true;
	m_playerName = PLAYER_NONE;
}

//---------------------
//	   コインの消失
//---------------------
void CCoin::Delete()
{
	m_state = ITEM_WAIT;
	m_playerName = PLAYER_NONE;
	m_isSpawn = true;
}

