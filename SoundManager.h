#pragma once
#include <xaudio2.h>
#ifndef SoundManager_H
#define SoundManager_H
#include "Sound.h"
#include "irrKlang.h"
using namespace irrklang;

#include <vector>
#include <iostream>
using namespace std;
static const char* sound_names[] = {
  "C:/Users/Liam/Desktop/Source/guitar.wav",
  "C:/Users/Liam/Desktop/Source/harp.wav",
  "C:/Users/Liam/Desktop/Source/piano.wav",
  "C:/Users/Liam/Desktop/Source/sax.wav",
  "C:/Users/Liam/Desktop/Source/trumpet.wav",
};
class SoundManager
{
public:
	// constructor
	SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator = (const SoundManager&) = delete;
	~SoundManager();


	void Initialize();
	void LoadSound();
	void Work();
	void Play(unsigned int index);
	void Stop(unsigned int index);
	void Pause(unsigned int index);
private:
	std::vector<Sound*> pPlayList;
	ISoundEngine* engine = NULL;

	bool IsPlaying = false;
};

#endif

//---  End of File ---

