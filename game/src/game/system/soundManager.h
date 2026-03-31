#pragma once
#include<DxLib.h>
#include<vector>

//定義ルール-------------------
//BGMID_名前	//名前のBGM
//SEID_名前		//名前の効果音
//-----------------------------

//定義関連------------------------------------------
//--------------------------------------------------

class CSoundManager
{
public:
	enum tagSound {
		BGM_GAME,		//BGM ゲーム本編
		BGM_TITLE,		//BGM タイトル
		BGM_RESULT,		//BGM リザルト
		BGM_SELECT,		//BGM 選択画面
		SE_GUN,			//SE 銃を撃った音
		SE_SWORD,		//SE 剣を振った音
		SE_AX,			//SE 斧を振った音
		SE_HAND,		//SE 素手で攻撃した音
		SE_HIT,			//SE 攻撃が当たった時の音
		SE_COINDROP,	//SE コインを落とした音
		SE_COINGET,		//SE コインを取得した音
		SE_BUY,			//SE アイテムを購入した音
		SE_EXPLOSION,	//SE 爆発音

		SOUND_NUM,		//BGM,SEの総数
	};

private:
	static std::vector<int> m_hndl;		//音楽ハンドル

public:
	//初期化
	static void Init();
	//音楽データ読み込み
	static void Load();
	// 終了処理
	static void Exit();

	//============================
	// 音楽再生関係
	//============================

	//音楽再生
	//_id		:再生する音楽のID
	//_type		:再生タイプ
	//			 DX_PLAYTYPE_BACK	:一回再生
	//			 DX_PLAYTYPE_LOOP	:ループ再生
	//_isStart	:true = 最初から再生, false = 途中から再生
	//return	:true = 再生成功, false = 再生失敗
	static bool Play(tagSound _id,
		int _type = DX_PLAYTYPE_BACK, bool _isStart = true);

	//音楽停止
	//@soundID	:	上記enumのどれかを渡す
	static void Stop(tagSound _iD);
	//全ての音楽の停止
	static void StopAll();

	//============================
	//　	取得関数
	//============================

	//再生時間取得(ミリ秒)
	//_id	:取得したい音楽のID
	//メモ	:圧縮形式の再生データは不可
	static int GetTime(tagSound _id);

	//再生総時間取得(ミリ秒)
	//_id	:取得したい音楽のID
	static int GetAllTime(tagSound _id);

	//音楽を再生中かを取得
	//_id	:再生中か確認したい音楽のID
	//return: true = 再生中, false = 停止中
	static bool IsPlay(tagSound _id);

	//=============================
	//		設定関数
	//=============================

	//再生開始時間設定
	//_id	:設定したい音楽のID
	//_ms	:再生開始時間(ミリ秒)
	//メモ	:Play()前に設定し、Play()では途中から再生すること
	//		使用時は必ず停止してからにすること
	static void SetStartFrame(tagSound _id, int _ms);

	//ボリューム設定
	//_id	:設定したい音楽のID
	//_vol	:ボリューム(0.0～1.0)
	static void SetVolume(tagSound _id, float _vol);
};


