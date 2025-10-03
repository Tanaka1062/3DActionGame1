#include"2DUi.h"

//---------------------------
//	コンストラクタ
//---------------------------
C2DUi::C2DUi()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = 0.0f;
	m_hndl = -1;
	m_isActive = true;
}

//---------------------------
//	デストラクタ
//---------------------------
C2DUi::~C2DUi()
{
	Exit();
}

//---------------------------
//	初期化
//---------------------------
void C2DUi::Init(VECTOR _pos, float _rot)
{
	m_pos = _pos;
	m_rot = _rot;
	m_hndl = -1;
	m_isActive = true;

}

//---------------------------
//	ロード
//---------------------------
void C2DUi::Load(const char* _hndlPath)
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph(_hndlPath);
	}
}

//---------------------------
//	毎フレームする処理
//---------------------------
void C2DUi::Step()
{

}

//---------------------------
//			描写
//---------------------------
void C2DUi::Draw(float _size)
{
	if (m_isActive == false)return;

	DrawRotaGraph((int)m_pos.x, (int)m_pos.y, _size, m_rot, m_hndl,TRUE);

}

//---------------------------
//			破棄
//---------------------------
void C2DUi::Exit()
{
	if (m_hndl != -1)
	{
		DeleteGraph(m_hndl);
		m_hndl = -1;
	}
}

//---------------------------
//	当たり判定後の処理
//---------------------------
void C2DUi::HitCalc()
{

}

//---------------------------
//	画像をロードする関数
//---------------------------
void C2DUi::LoadGraphic(int& _hndl, const char* _hndlPath, int _allNum,
	int _numX, int _numY, int _sizeX, int _sizeY)
{
	//ハンドルが空じゃなかったら処理をしない
	if (_hndl != -1)return;

	if (_allNum != 1)
	{
		LoadDivGraph(_hndlPath, _allNum, _numX, _numY, _sizeX, _sizeY,&_hndl);
	}
	else
	{
		_hndl = LoadGraph(_hndlPath);
	}
}
