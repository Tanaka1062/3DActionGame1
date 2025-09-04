#pragma once
#include "3DObject.h"

//3Dオブジェクトの基底クラス
class CActor :public CObject {
protected:
	//アニメーション関連のデータをまとめた構造体
	typedef struct {
		float	m_endFrame;		//アニメ全再生時間
		float	m_frame;		//アニメ再生時間
		float	m_speed;		//アニメ再生速度
		int		m_hndl;			//アニメハンドル
		int		m_id;			//再生中のアニメID
		int		m_state;		//アニメの状態(ループ再生かどうか)	
		bool	m_isEnd;		//アニメが終了しているかどうか
	}ANIM_DATA;

	ANIM_DATA m_animData;		//アニメ再生関連データ

public:
	//コンストラクタ
	CActor();

	//初期化
	virtual void Init();

	//更新処理
	virtual void Update();

	//アニメーション再生
	//_id		:どのアニメーションを再生するか
	//_speed	:アニメーションの再生速度
	//_isLoop	:アニメーションをループ再生するかどうか
	void Request(int _id, float _speed ,bool _isLoop = false);

private:
	//アニメーションをデタッチ
	void DetachAnim();

};