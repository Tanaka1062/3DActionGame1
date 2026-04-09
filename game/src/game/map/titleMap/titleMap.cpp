#include "titleMap.h"

//定義関連==================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };		//大きさ
static const char* MAP_MODEL_PATH ={
	"data/model/map/titleMap/titleMap.mv1",
};					//ロードするファイル名

//==========================================

//------------------------
//	コンストラクタ
//------------------------
CTitleMap::CTitleMap()
{
	m_stage.push_back(new CObject);
}

//------------------------
//		   初期化
//------------------------
void CTitleMap::Init()
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
void CTitleMap::Load()
{
	m_stage[0]->LoadModel(MAP_MODEL_PATH);
}

//------------------------
//	 毎フレームする処理
//------------------------
void CTitleMap::Step()
{
	
}

