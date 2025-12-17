#include "itemBase.h"
#include "../../lib/myMath/myMath.h"

constexpr float RADIUS = 7.5f;				//半径
constexpr float DROP_SPEED = 6.0f;			//飛ぶスピード
constexpr float DROP_JUMP = 7.0f;			//上に飛ぶ力

//--------------------------
//	   コンストラクタ
//--------------------------
CItemBase::CItemBase()
{
	Init();
}

//--------------------------
//		  初期化
//--------------------------
void CItemBase::Init()
{
	CActor::Init();

	m_rad = RADIUS;
	m_isActive = false;
	m_shadow.Init(m_pos,0.5f);	
	m_isGravity = true;
	m_isSpawn = false;
	m_isBuy = false;
	m_cost = 0;
	m_objectTypy = OBJECT_ITEM;
	m_state = ITEM_WAIT;
	m_itemName = ITEM_NONE;
	m_costUi.Init();

	//コストが0の場合はUI表示をしない
	if (m_cost == 0)
	{
		m_costUi.SetActive(false);
	}
}

//--------------------------
//モデルのロード(一つのモデルしか使わない)
//--------------------------
void CItemBase::Load(const char* _modelPath)
{
	CActor::LoadModel(_modelPath);
	m_shadow.Load();
	m_costUi.Load();
}

//--------------------------
//モデルのロード(同じモデルを複数使う場合)
//--------------------------
void CItemBase::Load(int _hndl)
{
	CActor::DuplicateModel(_hndl);
	m_shadow.Load();
	m_costUi.Load();
}

//--------------------------
//	 毎フレームする処理
//--------------------------
void CItemBase::Step()
{
	CActor::Step();
	//m_costUi.Step(m_pos,m_rad);

	m_shadow.Step(m_pos);

	if (m_pos.y <= -100.0f)
	{
		m_isActive = false;
	}
}

//--------------------------
//		  数値の更新
//--------------------------
void CItemBase::Update()
{
	CActor::Update();
	m_shadow.Update();
	m_costUi.Update();
}

//--------------------------
//		 モデルの描写
//--------------------------
void CItemBase::Draw()
{
	if (m_isActive == false)return;

	CActor::Draw();
	m_shadow.Draw();
	m_costUi.Draw();
}

//--------------------------
//		   終了処理
//--------------------------
void CItemBase::Exit()
{
	CActor::Exit();
	m_shadow.Exit();
	m_costUi.Exit();
}

//--------------------------
//	 使用した時の処理
//--------------------------
void CItemBase::Use()
{

}

//---------------------
//	アイテムのドロップ
//---------------------
void CItemBase::Drop(VECTOR _pos, float _rotY)
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
}

