#include "resultMap.h"
#include "../../player/playerData.h"

//定義関連==================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };	//大きさ
static const char* MAP_MODEL_PATH = {			//ロードするファイル名
	"data/model/map/resultMap/resultMap.mv1",
};					

static const char* OBJECT_MODEL_PATH = {		//オブジェクトのロードするファイル名
	"data/model/map/resultMap/podium.mv1",
};
constexpr int OBJECT_FRAME_NUM = 4;				//マップのオブジェクトの配置フレーム
constexpr float PODIUM_UP_SPEED = 0.001f;		//表彰台の動く速度
//==========================================

//------------------------
//	コンストラクタ
//------------------------
CResultMap::CResultMap()
{
	m_stage.push_back(new CActor);

	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_object.push_back(new CObject);
	}
}

//------------------------
//		   初期化
//------------------------
void CResultMap::Init()
{
	CMapBase::Init();
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stage[stage_i]->Init();
		m_stage[stage_i]->SetPos(ZERO);
	}
	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		m_object[object_i]->Init();
	}
}

//------------------------
//		モデルロード
//------------------------
void CResultMap::Load()
{
	m_stage[0]->LoadModel(MAP_MODEL_PATH);

	int frameNum = OBJECT_FRAME_NUM;
	int object_hndl = MV1LoadModel(OBJECT_MODEL_PATH);
	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		m_object[object_i]->DuplicateModel(object_hndl);
		m_object[object_i]->SetPos(MV1GetFramePosition(m_stage[0]->GetHndl(),frameNum));
		frameNum += 2;
	}
	MV1DeleteModel(object_hndl);

}

//------------------------
//	 毎フレームする処理
//------------------------
void CResultMap::Step()
{
	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		VECTOR scale = m_object[object_i]->GetScale();
		scale.y += PODIUM_UP_SPEED;
		m_object[object_i]->SetScale(scale);
	}
}

