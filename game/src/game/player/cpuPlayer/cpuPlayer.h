#pragma once
#include "../player.h"
#include "../../shot/shotManager.h"
#include"../../lib/input/controllerManager.h"
#include "../playerData.h"
#include "cpuPlayerFOV.h"

constexpr float CPU_JUMP_LENGTH = -30.0f;		//ジャンプ判定の長さ
constexpr float CPU_JUMP_RANGE = 5.0f;			//ジャンプ判定の範囲

//プレイヤークラス
class CCpuPlayer:public CPlayer
{
protected:
	enum tagCpuState							//CPUの行動状態
	{
		CPU_STATE_NONE = -1,					//初期化用
		CPU_STATE_ATTACK,						//攻撃状態
		CPU_STATE_PICK_UP_ITEM,					//アイテム拾い状態

		CPU_STATE_NUM,							//状態の数
	};
	
	int				m_cpuStateProbability[CPU_STATE_NUM];	//行動状態の確率
	tagCpuState		m_cpuState;								//行動状態
	CCpuPlayerFOV*	m_FOV;									//視界範囲クラス
	CObject*		m_targetObject;							//ターゲットになっているオブジェクト
	int				m_changeTime;							//状態が変化する時間
	bool			m_isHitAttack;							//攻撃が命中したかフラグ

public:
	//コンストラクタ
	CCpuPlayer();

	//初期化
	void Init(tagPlayerName _name, tagPadName _padName);

	//毎フレームする処理
	void Step(float _rotY,VECTOR* _targetPos, CAttackManager* _attackManager, CShotManager* _shotManager);

	//描写処理
	void Draw();

	//当たり判定後の処理
	void HitCalc(CObject* _hitObject);

	CCpuPlayerFOV* SetFOV(CCpuPlayerFOV* _FOV) { return m_FOV = _FOV; }

protected:
	
	//入力処理
	void InputStep(float _rotY);

	//移動処理
	void Move(float _rotY);

	//行動を変更
	void ChangeCpuState();

};

