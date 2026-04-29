#pragma once

#include <SDL.h>
#include <string>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    bool Initialize();
    void PlayAudioAsync(const std::string& filePath, int duration = -1, bool loop = false);  // Add duration and loop parameters
    void StopAudio();

private:
    static void AudioCallback(void* userdata, Uint8* stream, int len);

    SDL_AudioDeviceID audioDevice;
    SDL_AudioSpec audioSpec;
    Uint8* audioBuffer;
    Uint32 audioLength;
    Uint32 audioPosition;
    bool isLooping;         // Store whether to loop the audio
    int playbackDuration;   // Store the requested playback duration (in ms)
};


