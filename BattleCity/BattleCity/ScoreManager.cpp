#include "ScoreManager.h"

ScoreManager* ScoreManager::_instance = nullptr;

ScoreManager* ScoreManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new ScoreManager();
	}
	return _instance;
}

int ScoreManager::CalculateScore(int type, int num)
{
	return _scoreTank[type] * num;;
}

void ScoreManager::addScore(int score)
{
	_score += score;
}

int ScoreManager::getScore()
{
	return _score;
}

int ScoreManager::getHighScore()
{
	return _highScore;
}

ScoreManager::ScoreManager()
{
	_scoreTank[0] = 0;
	_scoreTank[1] = 0;
	_scoreTank[2] = 0;
	_scoreTank[3] = 0;
	_score = 0;
	_highScore = 30000;
	//get in file
}


ScoreManager::~ScoreManager()
{
}
