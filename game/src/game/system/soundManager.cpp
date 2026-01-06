#include "soundManager.h"

using namespace std;

vector<int> CSoundManager::m_hndl;


//---------------------------
//		初期化
//---------------------------
void CSoundManager::Init()
{
	//中身を空にする
	m_hndl.clear();
}

//---------------------------
//	音楽データ読み込み
//---------------------------
void CSoundManager::Load()
{
	// ロードする予定の音楽のパスを管理-----
	const char* SOUND_PATH[SOUND_NUM] = {
		"data/sound/game/gameBGM.mp3",
		"data/sound/title/titleBGM.mp3",
		"data/sound/result/resultBGM.mp3",
		"data/sound/select/selectBGM.mp3",
		"data/sound/game/gunSE.mp3",
		"data/sound/game/swordSE.mp3",
		"data/sound/game/axSE.mp3",
		"data/sound/game/handSE.mp3",
		"data/sound/game/hitSE.mp3",
		"data/sound/game/coinDropSE.mp3",
		"data/sound/game/coinGetSE.mp3",
		"data/sound/game/buySE.mp3",
		"data/sound/game/explosionSE.mp3",

	};
	// -------------------------------------

	for (int i = 0; i < SOUND_NUM; i++)
	{
		int hndl = LoadSoundMem(SOUND_PATH[i]);
		m_hndl.push_back(hndl);
	}

}

//---------------------------
//	終了処理
//---------------------------
void CSoundManager::Exit()
{
	for (int i = 0; i < m_hndl.size(); i++)
	{
		if (m_hndl[i] != -1)
		{
			DeleteSoundMem(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}

}

//============================
// 音楽再生関係
//============================

//---------------------------
//		音楽再生
//---------------------------
bool CSoundManager::Play(tagSound _id, int _type, bool _isStart)
{
	return PlaySoundMem(m_hndl[_id], _type,_isStart) ? true : false;
}

//---------------------------
//音楽停止
//---------------------------
void CSoundManager::Stop(tagSound soundID)
{
	StopSoundMem(m_hndl[soundID]);
}

//---------------------------
//全ての音楽の停止
//---------------------------
void CSoundManager::StopAll()
{
	for (int i = 0; i < m_hndl.size(); i++)
	{
		//とりあえずすべてをループして停止する
		StopSoundMem(m_hndl[i]);
	}

}

//============================
//　取得関数
//============================

//---------------------------
//再生時間取得(ミリ秒)
//---------------------------
int CSoundManager::GetTime(tagSound _id)
{
	return static_cast<int>(GetSoundCurrentTime(m_hndl[_id]));
}

//---------------------------
//再生総時間取得(ミリ秒)
//---------------------------
int CSoundManager::GetAllTime(tagSound _id)
{
	return static_cast<int>(GetSoundTotalTime(m_hndl[_id]));
}

//---------------------------
//音楽を再生中かを取得
//---------------------------
bool CSoundManager::IsPlay(tagSound _id)
{
	return CheckSoundMem(m_hndl[_id]) ? true : false;
}

//=============================
//		設定関数
//=============================

//---------------------------
//再生開始時間設定
//---------------------------
void CSoundManager::SetStartFrame(tagSound _id, int _ms)
{
	//指定IDの周波数を取得して設定
	int iFreq = GetFrequencySoundMem(m_hndl[_id]) * _ms / 1000;
	SetCurrentPositionSoundMem(iFreq, m_hndl[_id]);
}

//---------------------------
//ボリューム設定
//---------------------------
void CSoundManager::SetVolume(tagSound _id, float _vol)
{
	if (_vol < 0.0f || _vol>1.0f)return;
	ChangeVolumeSoundMem((int)(255.0f * _vol), m_hndl[_id]);
}

