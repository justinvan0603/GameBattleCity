#ifndef __SOUND_H__
#define __SOUND_H__

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

#include <dsound.h>
#include "DefaultConstant.h"
#include "CWaveFile.h"

class Sound
{
public:
	Sound(const char* audioPath);
	~Sound(void);

	static HRESULT initializeSoundClass(HWND windowsHandler);
	static HRESULT releaseSoundClass();

	HRESULT play(bool isLoop = false, DWORD priority = 0);
	HRESULT stop();

private:
	HRESULT loadAudio(const char* audioPath);

private:
	static WAVEFORMATEX _bufferFormat;
	static DSBUFFERDESC _bufferDescription;
	static LPDIRECTSOUND8 _audioHandler;
	static HWND _windowsHandler;

	LPDIRECTSOUNDBUFFER _soundBuffer;
};


#endif