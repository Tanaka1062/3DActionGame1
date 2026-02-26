#pragma once
#include "../player.h"
#include "../../shot/shotManager.h"
#include"../../lib/input/controllerManager.h"
#include "../playerData.h"
#include "cpuPlayerFOV.h"

//プレイヤークラス
class CCpuPlayer:public CPlayer
{
protected:
	enum tagCpuState							//CPUの行動状態
	{
		CPU_STATE_NONE = -1,
		CPU_STATE_ATTACK,
		CPU_STATE_PICK_UP_ITEM,

		CPU_STATE_NUM,
	};
	
	int m_cpuStateProbability[CPU_STATE_NUM];	//行動状態の確率
	tagCpuState m_cpuState;						//行動状態
	CCpuPlayerFOV* m_FOV;						//視界範囲クラス
	CObject* m_targetObject;					//ターゲットになっているオブジェクト
	int m_changeTime;							//状態が変化する時間

public:
	//コンストラクタ・デストラクタ
	CCpuPlayer();
	~CCpuPlayer();

	//初期化
	void Init(tagPlayerName _name, tagPadName _padName);

	//モデルロード
	void Load(int _modelHndl);

	//毎フレームする処理
	void Step(float _rotY,VECTOR* _targetPos, CAttackManager* _attackManager, CShotManager* _shotManager);

	//描写処理
	void Draw();

	//当たり判定後の処理
	void HitCalc(CObject* _hitObject);

	CCpuPlayerFOV* SetFOV(CCpuPlayerFOV* _FOV) { return m_FOV = _FOV; }

protected:

	//移動処理
	void Move(float _rotY);

	//ジャンプの呼び出し処理
	void RequestJump();

	//行動を変更
	void ChangeCpuState();

};

