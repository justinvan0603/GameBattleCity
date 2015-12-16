#include "Sound.h"

WAVEFORMATEX Sound::_bufferFormat;
DSBUFFERDESC Sound::_bufferDescription;
LPDIRECTSOUND8 Sound::_audioHandler;
HWND Sound::_windowsHandler;

// -----------------------------------------------
// Su dung duong dan de load am thanh vao buffer
// -----------------------------------------------
Sound::Sound(const char* audioPath)
{
	loadAudio(audioPath);
}



Sound::~Sound(void)
{
	_soundBuffer->Stop();
}


// -----------------------------------------------
// Khoi tao cac thuoc tinh de phuc vu cho viec load am thanh
// -----------------------------------------------
HRESULT Sound::initializeSoundClass(HWND windowsHandler)
{
	_windowsHandler = windowsHandler;

	HRESULT result;
	result = DirectSoundCreate8(0, &_audioHandler, 0);
	result = result | _audioHandler->SetCooperativeLevel(_windowsHandler, DSSCL_PRIORITY);

	ZeroMemory(&_bufferFormat, sizeof(WAVEFORMATEX));
	ZeroMemory(&_bufferDescription, sizeof(DSBUFFERDESC));

	_bufferFormat.wFormatTag = AUDIO_FORMAT_TAG;
	_bufferFormat.nChannels = AUDIO_NUM_OF_CHANNEL;
	_bufferFormat.nSamplesPerSec = AUDIO_SAMPLE_SPEED;
	_bufferFormat.wBitsPerSample = AUDIO_BITS_PER_SAMPLE;
	_bufferFormat.nBlockAlign = AUDIO_BLOCK_ALIGN(_bufferFormat.wBitsPerSample,
		_bufferFormat.nChannels);
	_bufferFormat.nAvgBytesPerSec = AUDIO_AVERAGE_BPS(_bufferFormat.nSamplesPerSec,
		_bufferFormat.nBlockAlign);

	_bufferDescription.dwFlags = AUDIO_FLAGS;
	_bufferDescription.guid3DAlgorithm = AUDIO_GUID;
	_bufferDescription.dwSize = sizeof(DSBUFFERDESC);

	return result;
}


HRESULT Sound::releaseSoundClass()
{
	if (_audioHandler != 0)
		return _audioHandler->Release();

	return S_OK;
}


// -----------------------------------------------
// Load am thanh vao buffer
// -----------------------------------------------
HRESULT Sound::loadAudio(const char* audioPath_)
{
	HRESULT result;
	CWaveFile audioObject;
	result = audioObject.Open(LPTSTR(audioPath_), 0, 1);

	if (!FAILED(result)) {

		_bufferDescription.dwBufferBytes = audioObject.GetSize();
		_bufferDescription.lpwfxFormat = audioObject.m_pwfx;

		result = _audioHandler->CreateSoundBuffer(&_bufferDescription, &_soundBuffer, 0);

		VOID* pointerToLockedBuffer = 0;
		DWORD lockedSize = 0;
		result = result | (_soundBuffer)->Lock(0, AUDIO_BUFFER_SIZE, &pointerToLockedBuffer,
			&lockedSize, 0, 0, DSBLOCK_ENTIREBUFFER);

		if (!FAILED(result)) {
			DWORD readedData = 0;
			audioObject.ResetFile();
			result = audioObject.Read((BYTE*)pointerToLockedBuffer, lockedSize, &readedData);
			if (!FAILED(result)) {
				(_soundBuffer)->Unlock(pointerToLockedBuffer, lockedSize, 0, 0);
			}
		}
	}

	audioObject.Close();
	return result;
}


// -----------------------------------------------
// Choi nhac
// -----------------------------------------------
HRESULT Sound::play(bool isLoop, DWORD priority)
{
	return _soundBuffer->Play(0, priority, isLoop & DSBPLAY_LOOPING);
}


// -----------------------------------------------
// Dung nhac
// -----------------------------------------------
HRESULT Sound::stop()
{
	HRESULT result = _soundBuffer->Stop();
	_soundBuffer->SetCurrentPosition(0);
	return result;
}