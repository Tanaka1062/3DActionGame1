#include "actor.h"

//アニメーションの再生タイプ
enum 
{
	ANIM_LOOP,
	ANIM_ENDLOOP,

};

//--------------------------
//		コンストラクタ
//--------------------------
CActor::CActor()
{
	Init();
}

//--------------------------
//		初期化
//--------------------------
void CActor::Init()
{
	//親クラスの変数を初期化
	CObject::Init();
	//m_animDataの中身を全て0にする
	ZeroMemory(&m_animData, sizeof(m_animData));
	//初期値が-1のものだけ設定
	m_animData.m_hndl = -1;
	m_animData.m_id = -1;
	m_animData.m_isEnd = false;
}

//--------------------------
//		更新処理
//--------------------------
void CActor::Update()
{
	//親クラスのUpdateを呼んでSRTを確定
	CObject::Update();

	//アニメーション更新処理==================================

	//アニメーションが再生されていなかったら処理をしない
	if (m_animData.m_hndl == -1)return;

	//アニメーションの時間を進める
	m_animData.m_frame += m_animData.m_speed;

	//最終フレームまで到達したか確認
	if (m_animData.m_frame >= m_animData.m_endFrame)
	{
		switch (m_animData.m_state)
		{
		case ANIM_LOOP:
			//ループ再生なら最初に戻す
			m_animData.m_frame = 0.0f;
			break;
		case ANIM_ENDLOOP:
			//最終フレームで止めるなら値を固定
			m_animData.m_frame = m_animData.m_endFrame;
			//isEndをtrueに
			m_animData.m_isEnd = true;
			break;
		}
	}

	//アニメーションの時間を更新
	MV1SetAttachAnimTime(m_hndl, m_animData.m_hndl,
		m_animData.m_frame);

	//========================================================

}

//--------------------------
//	アニメーション再生
//--------------------------
void CActor::Request(int _id, float _speed,bool _isLoop)
{
	//アニメーションをデタッチ
	DetachAnim();

	//アニメーションをアタッチ
	m_animData.m_hndl = MV1AttachAnim(m_hndl, _id);
	//初期フレームは0フレーム目に設定
	m_animData.m_frame = 0.0f;
	//このアニメの最終フレーム数を保存
	m_animData.m_endFrame = MV1GetAnimTotalTime(m_hndl, _id);
	//何番目のアニメを再生しているかを保存
	m_animData.m_id = _id;
	//アニメーションの再生速度を保存
	m_animData.m_speed = _speed;
	//アニメーションの再生タイプを保存
	if (_isLoop == true)
		m_animData.m_state = ANIM_LOOP;
	else
		m_animData.m_state = ANIM_ENDLOOP;
}

//--------------------------
//	アニメーションをデタッチ
//--------------------------
void CActor::DetachAnim()
{
	//再生中のアニメーションがあれば削除
	if (m_animData.m_hndl != -1)
	{
		MV1DetachAnim(m_hndl, m_animData.m_hndl);
		m_animData.m_hndl = -1;
	}

}

