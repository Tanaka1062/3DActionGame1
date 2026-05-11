#pragma once
#include<DxLib.h>
#include<iostream>
#include<vector>

//2Dのオブジェクト
class C2DObject
{
protected:
	VECTOR							m_pos;		//座標
	float							m_rot;		//回転角度
	std::vector<std::vector<int>>	m_hndl;		//モデルハンドル
	bool							m_isActive;	//生存フラグ

	typedef struct {
		int							m_frame;	//アニメの現在のフレーム
		int							m_timeCount;//アニメの時間
		int							m_speed;	//アニメの再生速度
		int							m_animId;	//現在のアニメID
		bool						m_animLoop;	//アニメループフラグ
	}ANIM_DATA;

	ANIM_DATA						m_animData;	//アニメ再生関連データ

public:
	//コンストラクタ・デストラクタ
	C2DObject();
	virtual ~C2DObject();

	//初期化(直接座標を設定する用)
	virtual void Init(VECTOR _pos, float _rot = 0.0f);
	//初期化(中身で初期化する用)
	virtual void Init();

	//ロード(直接画像をロードする用)
	//_hndlPath	:画像のパス
	//_allNum	:分割したときの画像の数(分割していなかったらここから下は入力しなくていい)
	//_sizeX	:分割した画像の大きさ横
	//_sizeY	:分割した画像の大きさ縦
	void Load(const char* _hndlPath, int _allNum = 1, int _sizeX = 1, int _sizeY = 1);
	//ロード(中身でロードする用)
	virtual void Load();

	//毎フレームする処理
	virtual void Step();
	//描写
	virtual void Draw(float _size = 1.0f);
	//破棄
	virtual void Exit();

	//当たり判定後の処理
	virtual void HitCalc();

protected:
	//画像をロードする関数
	//_hndlPath		:画像のパス
	//_allNum		:分割したときの画像の数(分割していなかったらここから下は入力しなくていい)
	//_sizeX		:分割した画像の大きさ横
	//_sizeY		:分割した画像の大きさ縦
	//メモ			:状態が複数ある場合は状態の数だけ呼び出してロードしてください
	void LoadGraphic(const char* _hndlPath,int _allNum = 1,  int _sizeX = 1, int _sizeY = 1);

	//画像のアニメーションを呼び出し
	//_animId	:再生させるアニメID
	//_animSpeed:何フレームで画像を進めるか
	//_isLoop	:ループ再生するか(デフォルトはループする)
	void RequestAnim(int _animId,int _animSpeed,bool _isLoop = true);

	//アニメーション再生
	void AnimStep();

	//アニメーション停止
	void AnimStop();

public:

	//座標を取得
	VECTOR GetPos() { return m_pos; }
	//角度を取得
	float GetRot() { return m_rot; }
	//生存フラグを取得
	bool GetActive() { return m_isActive; }


	//座標設定
	void SetPos(VECTOR _pos) { m_pos = _pos; }
	//角度設定
	void SetRot(float _rot) { m_rot = _rot; }
	//生存フラグを取得
	void SetActive(bool _active) { m_isActive = _active; }

	//ハンドルを取得
	void SetHndl(int _hndl) { m_hndl[0][0] = _hndl; }

	//アニメIDを設定
	void SetAnimId(int _animId)
	{
		//アニメーションの数より多い値は変更をしない
		if (m_hndl.size() < _animId)return;
		m_animData.m_animId = _animId;
	}

	//アニメのフレーム設定
	void SetAnimFrame(int _animFrame)
	{
		//画像の数より多い値は変更しない
		if (m_hndl[m_animData.m_animId].size() < _animFrame)return;
		m_animData.m_frame = _animFrame;
	}

};

