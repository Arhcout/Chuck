#pragma once
#include <stdbool.h>

typedef struct Audio_s {
  void *data;
  int channel;
  bool isPlaying;
} Audio;

int InitAudio();
void UninitAudio();
void PlayAudio(Audio *audio, int volume, bool loop);
bool IsPlayingAudio(Audio *audio);
void SetMasterVolume(float volume);
Audio *LoadAudio(const char *file);
void DestroyAudio(Audio *audio);
