#include "attackManager.h"

using namespace std;
CAttackManager* CAttackManager::m_instance = nullptr;

constexpr const char MODEL_PATH[] =
 "data/model/shot/shotTest.mv1" ;				//ロードするファイル名
constexpr int ATTACK_MAX = 30;					//攻撃の最大個数


//------------------------
//	  コンストラクタ
//------------------------
CAttackManager::CAttackManager()
{
	for (int attack_i = 0; attack_i < ATTACK_MAX; attack_i++)
	{
		m_attack.push_back(make_unique<CAttackBase>());
	}
	Init();
}

//------------------------
//	  デストラクタ
//------------------------
CAttackManager::~CAttackManager()
{
	Exit();

	//攻撃判定消去
	m_attack.clear();
}

//------------------------
//		 初期化
//------------------------
void CAttackManager::Init()
{
	for (int attack_i = 0; attack_i < m_attack.size(); attack_i++)
	{
		m_attack[attack_i]->Init();
	}
}

//------------------------
//		更新処理
//------------------------
void CAttackManager::Update()
{
	for (int attack_i = 0; attack_i < m_attack.size(); attack_i++)
	{
		if (m_attack[attack_i]->GetActive() == false)continue;
		m_attack[attack_i]->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CAttackManager::Draw()
{
	for (int attack_i = 0; attack_i < m_attack.size(); attack_i++)
	{
		m_attack[attack_i]->Draw();
	}

}

//------------------------
//		 終了処理
//------------------------
void CAttackManager::Exit()
{
	for (int attack_i = 0; attack_i < m_attack.size(); attack_i++)
	{
		m_attack[attack_i]->Exit();
	}
}

//------------------------
//	    攻撃の呼び出し
//------------------------
int CAttackManager::Request(VECTOR _pos, float _rad, int _atk, int _blown, tagPlayerName _name, int _num, int _nextTime)
{
	for (int attack_i = 0; attack_i < m_attack.size(); attack_i++)
	{
		if (m_attack[attack_i]->GetActive() == false)
		{
			m_attack[attack_i]->Init();
			m_attack[attack_i]->Request(_pos, _rad, _atk, _blown, _name, _num, _nextTime);
			return attack_i;
		}
	}

	return -1;
}

//------------------------
//攻撃の当たり判定のアドレスを取得
//------------------------
CAttackBase* CAttackManager::GetAttack(int _num)
{
	//引数より攻撃の数が少なければnullを返す
	if (_num > m_attack.size())return nullptr;
	return m_attack[_num].get();
}

//------------------------
//	攻撃の座標を設定する
//------------------------
void CAttackManager::SetPos(int _num, VECTOR _pos)
{
	if (m_attack.size() < _num)return;

	m_attack[_num]->SetPos(_pos);
}

//------------------------
//攻撃の生存フラグを取得
//------------------------
bool CAttackManager::GetActive(int _num)
{
	if (m_attack.size() < _num)return false;

	return m_attack[_num]->GetActive();
}

//------------------------
//攻撃の生存フラグを設定
//------------------------
void CAttackManager::SetActive(int _num, bool _active)
{
	if (m_attack.size() < _num)return;

	m_attack[_num]->SetActive(_active);
}

//------------------------
//攻撃のヒットフラグを取得
//------------------------
bool CAttackManager::GetIsHit(int _num)
{
	if (m_attack.size() < _num)return false;

	return m_attack[_num]->GetIsHit();
}

