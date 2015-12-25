#pragma once
#include<Windows.h>
class GameTime
{
private:
//	DWORD _fps;
	DWORD _deltaTime;	//Khoang thoi gian giua startTime va now
	DWORD _deltaTimePrevious;
	DWORD _timePerFrame;	//Tinh theo cong thuc 1000 (milisec) /fps (so khung hinh tren 1giay)
	DWORD _startTime;	//
	DWORD _now;

public:
	static int _tick;
	GameTime(float fps);
	static bool RenderFrame(DWORD& startTime, float delayTime);
	static bool DelayTime(int& delayTime);
	DWORD GetTimePerFrame();
	~GameTime();
};

