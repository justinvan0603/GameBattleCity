#include "Sound.h"
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib" )

DSound::DSound(HWND hWnd) : _directSoundDevice(NULL), _primaryBuffer(NULL)
{
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	//Create sound Device
	DirectSoundCreate8(NULL, &_directSoundDevice, NULL);
	//Set Cooperative for window
	_directSoundDevice->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	//Set buffer Decription
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;
	//Create buffer by device
	_directSoundDevice->CreateSoundBuffer(&bufferDesc, &_primaryBuffer, NULL);

	//set buffer Wave Format
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
	
	_primaryBuffer->SetFormat(&waveFormat);
}

DSound::~DSound()
{
	if (_primaryBuffer)
	{
		_primaryBuffer->Release();
		_primaryBuffer = NULL;
	}
	if (_directSoundDevice)
	{
		_directSoundDevice->Release();
		_directSoundDevice = NULL;
	}
}

Sound DSound::CreateSound(char* waveFileName)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	IDirectSoundBuffer8* pSecondaryBuffer;
	unsigned char* waveData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	fopen_s(&filePtr, waveFileName, "rb");

	fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
	
	waveFileHeader.dataSize = 9990000;

	// Set the buffer description of the secondary sound buffer
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	//Create temporary sound buffer
	_directSoundDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pSecondaryBuffer);
	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.dataSize];

	// Read in the wave file data into the newly created buffer.
	fread(waveData, 1, waveFileHeader.dataSize, filePtr);

	// Close the file once done reading.
	fclose(filePtr);

	// Lock the secondary buffer to write wave data into it.
	pSecondaryBuffer->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	pSecondaryBuffer->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = NULL;

	return Sound(pSecondaryBuffer);
}

Sound::Sound(IDirectSoundBuffer8* secondaryBuffer) :_buffer(secondaryBuffer)
{
}

Sound::Sound() : _buffer(NULL)
{}

Sound::Sound(const Sound& base) : _buffer(base._buffer)
{
	_buffer->AddRef();
}

Sound::~Sound()
{
	if (_buffer)
	{
		_buffer->Release();
		_buffer = NULL;
	}
}

const Sound& Sound:: operator =(const Sound& source)
{
	this->~Sound();
	_buffer = source._buffer;
	_buffer->AddRef();
	return source;
}

void Sound::Play(int attenuation)
{
	attenuation = max(attenuation, DSBVOLUME_MIN);
	HRESULT result;

	// Set position at the beginning of the sound buffer.
	_buffer->SetCurrentPosition(0);

	// Set volume of the buffer to attn
	_buffer->SetVolume(attenuation);

	// Play the contents of the secondary sound buffer.
	_buffer->Play(0, 0, 0);
}

void Sound::PlayeRepeat(int attenuation)
{
	attenuation = max(attenuation, DSBVOLUME_MIN);
	HRESULT result;

	// Set position at the beginning of the sound buffer.
	_buffer->SetCurrentPosition(0);


	// Set volume of the buffer to attn
	_buffer->SetVolume(attenuation);

	// Play the contents of the secondary sound buffer.
	_buffer->Play(0, 0, DSBPLAY_LOOPING);
}

void Sound::Stop()
{
	_buffer->Stop();
}