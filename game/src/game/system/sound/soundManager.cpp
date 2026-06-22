#include "soundManager.h"

using namespace std;

vector<int> CSoundManager::m_hndl;

constexpr int SOUND_VOLUME[CSoundManager::tagSound::SOUND_NUM] =
{
	150,
	150,
	150,
	150,
	150,
	255,
	255,
	255,
	255,
	255,
	255,
	255,
	255,
	255,
	255,
	255,
	255,
	255,

};

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
		"data/sound/result/drumrollBGM.mp3",
		"data/sound/select/selectBGM.mp3",
		"data/sound/title/titleStartSE.mp3",
		"data/sound/select/joinSE.mp3",
		"data/sound/select/readyOnSE.mp3",
		"data/sound/select/readyOffSE.mp3",
		"data/sound/game/hammerSE.mp3",
		"data/sound/game/axSE.mp3",
		"data/sound/game/handSE.mp3",
		"data/sound/game/hitSE.mp3",
		"data/sound/game/coinDropSE.mp3",
		"data/sound/game/coinGetSE.mp3",
		"data/sound/game/explosionSE.mp3",
		"data/sound/result/podiumStopSE.mp3",
		"data/sound/result/applauseSE.mp3",
	};
	// -------------------------------------

	for (int sound_i = 0; sound_i < SOUND_NUM; sound_i++)
	{
		int hndl = LoadSoundMem(SOUND_PATH[sound_i]);
		m_hndl.push_back(hndl);
		ChangeVolumeSoundMem(SOUND_VOLUME[sound_i], hndl);
	}

}

//---------------------------
//	終了処理
//---------------------------
void CSoundManager::Exit()
{
	for (int sound_i = 0; sound_i < m_hndl.size(); sound_i++)
	{
		if (m_hndl[sound_i] != -1)
		{
			DeleteSoundMem(m_hndl[sound_i]);
			m_hndl[sound_i] = -1;
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
	int result = PlaySoundMem(m_hndl[_id], _type, _isStart);

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
	for (int sound_i = 0; sound_i < m_hndl.size(); sound_i++)
	{
		//とりあえずすべてをループして停止する
		StopSoundMem(m_hndl[sound_i]);
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

