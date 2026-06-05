#include"2DObject.h"

using namespace std;

//---------------------------
//	コンストラクタ
//---------------------------
C2DObject::C2DObject()
{
	Init();

	//画像ハンドルを一つだけ作成する
	vector<int>hndl;
	hndl.push_back(-1);
	m_hndl.push_back(hndl);
}

//---------------------------
//	デストラクタ
//---------------------------
C2DObject::~C2DObject()
{
	Exit();
}

//---------------------------
//初期化(直接座標を設定する用)
//---------------------------
void C2DObject::Init(VECTOR _pos, float _rot)
{
	m_pos = _pos;
	m_rot = _rot;
	m_isActive = true;
	m_animData.m_frame = 0;
	m_animData.m_timeCount = 0;
	m_animData.m_speed = 0;
	m_animData.m_animId = 0;
	m_animData.m_animLoop = false;
}

//---------------------------
//初期化(中身で初期化する用)
//---------------------------
void C2DObject::Init()
{
	Init(VGet(0.0f,0.0f,0.0f));
}

//---------------------------
//	ロード (直接画像をロードする用)
//---------------------------
void C2DObject::Load(const char* _hndlPath, int _allNum, int _sizeX, int _sizeY)
{
	LoadGraphic(_hndlPath,_allNum,_sizeX,_sizeY);
}

//---------------------------
//	ロード(中身でロードする用)
//---------------------------
void C2DObject::Load()
{

}

//---------------------------
//	毎フレームする処理
//---------------------------
void C2DObject::Step()
{
	AnimStep();
}

//---------------------------
//			描写
//---------------------------
void C2DObject::Draw(float _size)
{
	if (m_isActive == false || m_hndl.size() == 0)return;
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), _size, m_rot, m_hndl[m_animData.m_animId][m_animData.m_frame], TRUE);

}

//---------------------------
//			破棄
//---------------------------
void C2DObject::Exit()
{
	for (int animNum_i = 0; animNum_i < m_hndl.size(); animNum_i++)
	{
		for (int hndl_i = 0; hndl_i < m_hndl[animNum_i].size(); hndl_i++)
		{
			if (m_hndl[animNum_i][hndl_i] != -1)
			{
				DeleteGraph(m_hndl[animNum_i][hndl_i]);
				m_hndl[animNum_i][hndl_i] = -1;
			}
		}
	}
}

//---------------------------
//	当たり判定後の処理
//---------------------------
void C2DObject::HitCalc()
{

}

//---------------------------
//画像のアニメーションを呼び出し
//---------------------------
void C2DObject::RequestAnim(int _animId, int _animSpeed, bool _isLoop)
{
	//現在のアニメーションに存在しない場合は処理をしない
	if (m_hndl.size() < _animId)return;

	//アニメーションを設定
	m_animData.m_animId = _animId;
	m_animData.m_timeCount = 0;
	m_animData.m_frame = 0;
	m_animData.m_speed = _animSpeed;
	m_animData.m_animLoop = _isLoop;
}

//---------------------------
//	   アニメーション再生
//---------------------------
void C2DObject::AnimStep()
{
	//画像が無い場合はアニメーションをしない
	if (m_hndl.size() == 0)return;

	//最後まで到達していなかったらアニメーションを進める
	if (m_hndl[m_animData.m_animId].size() - 1 > m_animData.m_frame)
	{
		m_animData.m_timeCount++;

		//アニメ速度をタイムが超えたらアニメーションを進める
		if (m_animData.m_speed <= m_animData.m_timeCount)
		{
			m_animData.m_frame++;
			m_animData.m_timeCount = 0;
		}
	}
	//ループ再生するなら最初に戻す
	else if (m_animData.m_animLoop == true)
	{
		m_animData.m_frame = 0;
	}

}

//---------------------------
//	  アニメーション停止
//---------------------------
void C2DObject::AnimStop()
{
	//アニメーションがすでに止まっている場合は処理をしない
	if (m_animData.m_speed == 0)return;

	m_animData.m_speed = 0;
}

//---------------------------
//	画像をロードする関数
//---------------------------
void C2DObject::LoadGraphic(const char* _hndlPath, int _allNum , int _sizeX, int _sizeY)
{
	//ハンドルが空なら処理をしない
	if (_hndlPath == nullptr)return;

	vector<int> hndl;

	//一枚だけの場合
	if (_allNum == 1)
	{
		if (m_hndl[0][0] == -1)
		{
			//画像を一枚ロードする
			m_hndl[0][0] = LoadGraph(_hndlPath);
		}
	}
	//複数ある場合は分けてロードする
	else
	{
		//分割分ハンドルを作成する
		for (int hndl_i = 0; hndl_i < _allNum; hndl_i++)
		{
			hndl.push_back(-1);
		}

		//画像をロードする
		LoadDivGraph(_hndlPath, _allNum, _allNum , 1, _sizeX, _sizeY, &hndl[0]);

		//一番最初の画像が無い場合消す
		if (m_hndl[0][0] == -1)
		{
			m_hndl.clear();
		}
		
		//ロードした画像を追加する
		m_hndl.push_back(hndl);
	}
}


