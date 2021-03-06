#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"

#include "List.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;//NAMING CONVENTION NOT CHANGED BEACUSE IT WAS FROM SDL MIXER, not our code
struct Mix_Chunk;

class AudioManager : public Module
{
public:

	AudioManager();

	// Destructor
	virtual ~AudioManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	void VolumeMusic(int volume);
	void VolumeFx(int volume);

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	int volumeMusic;
	int volumeFx;
	bool fullscreenCheck;
	bool vsyncCheck;
private:

	_Mix_Music* music;
	List<Mix_Chunk*> fx;
};

#endif // __AUDIO_H__