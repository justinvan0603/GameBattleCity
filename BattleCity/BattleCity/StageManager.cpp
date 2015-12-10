#include "StageManager.h"
#include "GameDefaultConstant.h"

StageManager* StageManager::_instance = nullptr;

StageManager* StageManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new StageManager();
	}
	return _instance;
}

void StageManager::nextStage()
{
	_currentStage++;
}

int StageManager::getStage()
{
	return _currentStage;
}

void StageManager::reset()
{
	_currentStage = DEFAULT_START_STAGE;
}

StageManager::StageManager()
{
	_maxStage = DEFAULT_MAX_STAGE;
	_currentStage = DEFAULT_START_STAGE;
}


StageManager::~StageManager()
{
}
