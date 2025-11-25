#include "itemBase.h"

static const float RADIUS = 7.5f;		//半径

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
	CObject::Init();

	m_rad = RADIUS;
	m_isActive = false;
	m_shadow.Init(m_pos,0.5f);	
	m_isGravity = true;
	m_isSpawn = true;
	m_objectTypy = OBJECT_ITEM;
	m_state = ITEM_WAIT;

}

//--------------------------
//モデルのロード(一つのモデルしか使わない)
//--------------------------
void CItemBase::Load(const char* _modelPath)
{
	CObject::LoadModel(_modelPath);
	m_shadow.Load();
}

//--------------------------
//モデルのロード(同じモデルを複数使う場合)
//--------------------------
void CItemBase::Load(int _hndl)
{
	CObject::DuplicateModel(_hndl);
	m_shadow.Load();
}

//--------------------------
//	 毎フレームする処理
//--------------------------
void CItemBase::Step()
{
	CObject::Step();

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
	CObject::Update();
	m_shadow.Update();
}

//--------------------------
//		 モデルの描写
//--------------------------
void CItemBase::Draw()
{
	if (m_isActive == false)return;

	CObject::Draw();
	m_shadow.Draw();
}

//--------------------------
//		   終了処理
//--------------------------
void CItemBase::Exit()
{
	CObject::Exit();
	m_shadow.Exit();
}

//--------------------------
//	 使用した時の処理
//--------------------------
void CItemBase::Use()
{

}

