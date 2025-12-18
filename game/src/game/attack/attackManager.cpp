#include "attackManager.h"

using namespace std;

static const char MODEL_PATH[] =
 "data/model/shot/shotTest.mv1" ;				//ロードするファイル名

list<CAttackBase*> CAttackManager::m_attack;

//------------------------
//	  コンストラクタ
//------------------------
CAttackManager::CAttackManager()
{
	Init();
}

//------------------------
//	  デストラクタ
//------------------------
CAttackManager::~CAttackManager()
{
	Exit();
}

//------------------------
//		 初期化
//------------------------
void CAttackManager::Init()
{
}

//------------------------
//		更新処理
//------------------------
void CAttackManager::Update()
{
	for (auto ite = m_attack.begin(); ite != m_attack.end();)
	{
		//毎フレームする処理
		(*ite)->Update();

		//生存してない攻撃の当たり判定を消す
		if ((*ite)->GetActive() == false)
		{
			//終了処理
			(*ite)->Exit();

			delete (*ite);

			ite = m_attack.erase(ite);
		}
		else
		{
			++ite;
		}

	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CAttackManager::Draw()
{
	for (auto ite = m_attack.begin(); ite != m_attack.end(); ++ite)
	{
		//描写処理
		(*ite)->Draw();
	}
}

//------------------------
//		 終了処理
//------------------------
void CAttackManager::Exit()
{
	for (auto ite = m_attack.begin(); ite != m_attack.end();)
	{
		//終了処理
		(*ite)->Exit();

		delete (*ite);

		//終了処理が終わった攻撃判定を消す
		ite = m_attack.erase(ite);
	}
}

//------------------------
//	    攻撃の呼び出し
//------------------------
void CAttackManager::Request(VECTOR _pos, float _rad, int _atk, int _blown, tagPlayerName _name, int _num, int _nextTime)
{
	//攻撃の当たり判定のベースクラスにデータを入力
	CAttackBase* attack = new CAttackBase;
	attack->Init();
	attack->Request(_pos, _rad, _atk, _blown, _name, _num, _nextTime);

	//攻撃の当たり判定を追加
	m_attack.push_back(attack);
}

//------------------------
//攻撃の当たり判定のアドレスを取得
//------------------------
CAttackBase* CAttackManager::GetAttack(int _num)
{
	//引数より攻撃の数が少なければnullを返す
	if (_num > m_attack.size())return nullptr;
	//攻撃の数をカウントする変数
	int count = 0;
	for (auto ite = m_attack.begin(); ite != m_attack.end(); ++ite)
	{
		//引数の数字と同じならアドレスを返す
		if (count == _num)
		{
			return *ite;
		}
		count++;

	}
	return nullptr;
}

