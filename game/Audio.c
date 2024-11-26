#include "Audio.h"
#include "Files.h"
#include <Error.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define CHANNEL_NUMBER 32

static float _masterVolume = 1.0f;

static Audio *_playing[CHANNEL_NUMBER];

static void _Callback_ChannelFinished(int channel) {
  _playing[channel]->isPlaying = false;
  _playing[channel] = NULL;
}

int InitAudio() {
  if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0) {
    ERROR("Can't init SDL_mixer: %s\n", SDL_GetError());
    return -1;
  }

  // open 22KHz, signed 16bit, system byte order,
  //      stereo audio, using 1024 byte chunks
  if (!Mix_OpenAudio(0, NULL)) {
    ERROR("Can't open audio SDL_mixer: %s\n", SDL_GetError());
    return -1;
  }

  if (Mix_AllocateChannels(CHANNEL_NUMBER) < 1) {
    ERROR("Can't Allocate audio channels SDL_mixer: %s\n", SDL_GetError());
    return -1;
  }

  Mix_ChannelFinished(_Callback_ChannelFinished);

  return 0;
}

static int _LoadWAV(const char *path, Audio *out) {
  assert(path);
  assert(out);
  char *full = GetOSPath(path);
  if (GetError() != LOG_LV) {
    return 0;
  }
  out->data = Mix_LoadWAV(full);
  if (out->data == NULL) {
    ERROR("Can't open path: %s\n", path);
    return 0;
  }
  return 1;
}

Audio *LoadAudio(const char *file) {
  assert(file);
  Audio *ret = malloc(sizeof(Audio));
  assert(ret);
  // Get extention of file
  const char *ext = file;
  while (*ext != '.')
    ext++;
  // Is file WAV
  if (strncmp(ext, ".wav", 1024) == 0) {
    if (_LoadWAV(file, ret) == 0) {
      free(ret);
      return NULL;
    }
  } else {
    WARNING("Extention not implemented\n");
    return NULL;
  }
  return ret;
}

void DestroyAudio(Audio *audio) {
  Mix_FreeChunk(audio->data);
  free(audio);
}

void PlayAudio(Audio *audio, int volume, bool loop) {
  assert(audio);
  int channel = Mix_PlayChannel(-1, audio->data, -1 ? loop : 1);
  if (channel < 0) {
    WARNING("Cant play audio SDL_mixer: %s\n", SDL_GetError());
    return;
  }
  Mix_Volume(channel, (int)(volume * _masterVolume));

  audio->channel = channel;
  audio->isPlaying = true;
  _playing[channel] = audio;
}

bool IsPlayingAudio(Audio *audio) {
  assert(audio);
  return audio->isPlaying;
}

void SetMasterVolume(float volume) {
  if (volume < 0.0f)
    volume = 0.0f;
  else if (volume > 1.0f)
    volume = 1.0f;

  _masterVolume = volume;
}

void UninitAudio() {
  Mix_CloseAudio();
  Mix_Quit();
}
