#pragma once
#include<thread>
#include "irrKlang.h"
using namespace irrklang;
#pragma comment(lib,"irrKlang.lib")

class Sound {
private:
	ISound* music;
	char* filepath;
public:
	Sound(ISoundEngine* engine, char* filepath) {
		this->filepath = filepath;
		music = engine->play3D(filepath, vec3df(0, 0, 0), true, true, true);
	}
	void Play() {
		if (music->getIsPaused()) {
			Resume();

		}
		else {
			Pause();
		}
		//"../BackgroundMusic.wav"


	}
	void Stop() {
		//"../BackgroundMusic.wav"
		music->stop();

	}
	void setVolume(float vol) {
		music->setVolume(vol);
	}
	float getVolume() {
		return music->getVolume();
	}
	void Pause() {
		if (!music->getIsPaused()) {
			music->setIsPaused();
		}
	}
	void Resume() {
		if (music->getIsPaused()) {
			music->setIsPaused(false);
		}
	}
};