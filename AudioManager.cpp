#include "AudioManager.h"
#include <iostream>
#include <thread>
#include <chrono>

AudioManager::AudioManager() : audioDevice(0), audioBuffer(nullptr), audioLength(0), audioPosition(0), isLooping(false), playbackDuration(-1) {}

AudioManager::~AudioManager() {
    StopAudio();
}

bool AudioManager::Initialize() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void AudioManager::PlayAudioAsync(const std::string& filePath, int duration, bool loop) {
    // Load the WAV file
    if (SDL_LoadWAV(filePath.c_str(), &audioSpec, &audioBuffer, &audioLength) == nullptr) {
        std::cerr << "Failed to load WAV file! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    audioPosition = 0;
    isLooping = loop;
    playbackDuration = duration;

    // Set up the audio callback
    audioSpec.callback = AudioCallback;
    audioSpec.userdata = this;

    // Open the audio device
    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, 0);
    if (audioDevice == 0) {
        std::cerr << "Failed to open audio device! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Start playing
    SDL_PauseAudioDevice(audioDevice, 0);

    // Create a thread to manage the playback duration
    if (playbackDuration > 0) {
        std::thread([this]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(this->playbackDuration));
            this->StopAudio();
            }).detach();
    }
}

void AudioManager::StopAudio() {
    if (audioDevice != 0) {
        SDL_CloseAudioDevice(audioDevice);
        audioDevice = 0;
    }
    if (audioBuffer != nullptr) {
        SDL_FreeWAV(audioBuffer);
        audioBuffer = nullptr;
    }
}

void AudioManager::AudioCallback(void* userdata, Uint8* stream, int len) {
    AudioManager* manager = static_cast<AudioManager*>(userdata);

    if (manager->audioPosition >= manager->audioLength) {
        if (manager->isLooping) {
            manager->audioPosition = 0;  // Loop back to the start
        }
        else {
            return;  // End the callback if not looping
        }
    }

    // Copy audio data
    Uint32 remaining = manager->audioLength - manager->audioPosition;
    Uint32 bytesToWrite = (len > remaining) ? remaining : len;
    SDL_memcpy(stream, manager->audioBuffer + manager->audioPosition, bytesToWrite);

    // Update position
    manager->audioPosition += bytesToWrite;
}
