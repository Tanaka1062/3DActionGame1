#include "cpuPlayerFOV.h"
#include "../../item/itemBase.h"
#include "../../item/itemObject/itemObjectBase.h"
#include "cpuPlayer.h"

using namespace std;

constexpr float RADIUS = 400.0f;							//半径

CCpuPlayerFOV::CCpuPlayerFOV()
{
	Init();
}

CCpuPlayerFOV::~CCpuPlayerFOV()
{
	Exit();
}

//初期化
void CCpuPlayerFOV::Init()
{
	CObject::Init();
	m_hitObject.clear();
	m_objectBuf.clear();
	m_objectTypy = OBJECT_FOV;
	m_isPushed = false;
	m_isActive = true;
	m_isGravity = false;
	m_rad = RADIUS;
}

//毎フレームする処理
void CCpuPlayerFOV::Step(CObject* _object)
{
	m_owner = _object;

	m_pos.y -= RADIUS;

	//保存しているオブジェクトを初期化
	m_objectBuf.clear();

	//当たっているオブジェクトを保存
	for (auto hitObject_i = m_hitObject.begin(); hitObject_i != m_hitObject.end();hitObject_i++)
	{
		m_objectBuf.push_back(*hitObject_i);
	}

	//当たっているオブジェクトの初期化
	m_hitObject.clear();
}

//当たり判定後の処理
void CCpuPlayerFOV::HitCalc(CObject* _hitObject)
{
	//プレイヤーとアイテムを保存する
	if (_hitObject->GetObjectType() == OBJECT_PLAYER)
	{
		m_hitObject.push_back(_hitObject);
	}

	//アイテムの場合------------------------------------------
	if (_hitObject->GetObjectType() == OBJECT_ITEM)
	{
		CItemBase* item = dynamic_cast<CItemBase*>(_hitObject);

		if (m_owner != nullptr)
		{
			CCpuPlayer* player = dynamic_cast<CCpuPlayer*>(m_owner);
			//持っているコインより値段が高いアイテムは無視する
			if (item->GetCost() > player->GetMoney())return;
		}

		if (item->GetItemType() == ITEM_TYPE_OBJECT)
		{
			CItemObjectBase* itemObject = dynamic_cast<CItemObjectBase*>(item);

			if (itemObject->GetIsLift() == true)
			{
				return;
			}
		}

		m_hitObject.push_back(_hitObject);
	}
	//--------------------------------------------------------
}

