#include "selectMap.h"

using namespace std;

//定義関連==================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };		//大きさ
constexpr const char* MAP_MODEL_PATH ={
	"data/model/map/selectMap/selectMap.mv1",
};					//ロードするファイル名

//==========================================

//------------------------
//	コンストラクタ
//------------------------
CSelectMap::CSelectMap()
{
	m_stage.push_back(make_unique<CActor>());
}

//------------------------
//		   初期化
//------------------------
void CSelectMap::Init()
{
	CMapBase::Init();
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stage[stage_i]->Init();
		m_stage[stage_i]->SetPos(ZERO);
	}
}

//------------------------
//		モデルロード
//------------------------
void CSelectMap::Load()
{
	m_stage[0]->LoadModel(MAP_MODEL_PATH);
}

//------------------------
//	 毎フレームする処理
//------------------------
void CSelectMap::Step()
{
	
}

