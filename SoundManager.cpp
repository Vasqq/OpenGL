#include "SoundManager.h"
SoundManager::~SoundManager()
{
	for (Sound* sound : pPlayList) if (sound)
		delete sound;
}
void SoundManager::Initialize() {

	if (engine == NULL) {
		engine = createIrrKlangDevice();
	}
}

void SoundManager::Work() {

}
void SoundManager::LoadSound()
{
	pPlayList.clear();
	for (int i = 0; i < 5; i++) {
		Sound* sound = new Sound(engine, (char*)sound_names[i]);
		pPlayList.push_back(sound);
	}
}



void SoundManager::Pause(unsigned int index) {
	if (index <0 || index >pPlayList.size()) {
		return;
	}

	pPlayList[index]->Pause();
}
void SoundManager::Stop(unsigned int index) {
	if (index <0 || index >pPlayList.size()) {
		return;
	}

	pPlayList[index]->Stop();

}
void SoundManager::Play(unsigned int index) {
	if (index <0 || index >pPlayList.size()) {
		return;
	}

	pPlayList[index]->Play();
}