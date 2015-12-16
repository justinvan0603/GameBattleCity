#include "GameTime.h"

int GameTime::_tick = 0;

GameTime::GameTime(float fps)
{
	_timePerFrame = 1000.0 / fps;
	_startTime = GetTickCount();
}
bool GameTime::CanCreateFrame()
{
	_now = GetTickCount();
	_deltaTime = _now - _startTime;
	if (_deltaTime >= _timePerFrame)
	{
		_startTime += _now;
		return true;
	}
	return false;
}
bool GameTime::RenderFrame(DWORD& startTime, float delayTime)
{
	DWORD now = GetTickCount();
	DWORD deltaTime = now - startTime;
	if (deltaTime >= delayTime)
	{
		startTime = now;
		return true;
	}
	return false;
}

//----------------------------------
// Set khoang thoi gian delay de chay 1 ham nao do
//----------------------------------
bool GameTime::DelayTime(int& delayTime)
{
	delayTime -= 50;
	if(delayTime < 0)
		return true;
	return false;
}

DWORD GameTime::GetTimePerFrame()
{
	return _timePerFrame;
}


GameTime::~GameTime()
{
}
