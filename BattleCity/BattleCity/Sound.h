#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>

class DSound;

class Sound
{
	friend DSound;
private:
	Sound(IDirectSoundBuffer8* pSecondaryBuffer);
	IDirectSoundBuffer8* _buffer;
public:
	Sound();
	Sound(const Sound& base);
	const Sound& operator= (const Sound& source);
	void Play(int attenuation = DSBVOLUME_MAX);
	void PlayRepeat(int attenuation = DSBVOLUME_MAX);
	void Stop();
	~Sound();
};


class DSound
{
private:
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
private:
	IDirectSoundBuffer* _primaryBuffer;
	IDirectSound8* _directSoundDevice;
public:
	DSound(){};
	DSound(HWND hWnd); 
	~DSound();
	Sound CreateSound(char* waveFileName);
};