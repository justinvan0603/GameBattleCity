#include "ScoreManager.h"
#include "GameDefaultConstant.h"


ScoreManager* ScoreManager::_instance = nullptr;

ScoreManager* ScoreManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new ScoreManager();
	}
	return _instance;
}

int ScoreManager::getPlayerScore()
{
	return _playerScore;
}

int ScoreManager::getHighScore()
{
	if (_playerScore > _highScore)
		_highScore = _playerScore;
	return _highScore;
}

void ScoreManager::addKillTankScore(int typeTank)
{
	_playerScore += _scoreTank[typeTank];
	_numTank[typeTank]++;
}

void ScoreManager::addPowerUpScore()
{
	_playerScore += _scorePowerUp;
}

int ScoreManager::getNumTank(int typeTank)
{
	return _numTank[typeTank];
}

int ScoreManager::getNumTank()
{
	int temp = 0;
	for (int i = 0; i < NUM_TYPE_ENEMY;i++)
	{
		temp += _numTank[i];
	}
	return temp;
}

void ScoreManager::renewValue()
{
	for (int i = 0; i < NUM_TYPE_ENEMY; i++)
	{
		_numTank[i] = 0;
	}
}

void ScoreManager::reset()
{
	_playerScore = 0;
}

int ScoreManager::getScoreTank(int typeTank)
{
	return _numTank[typeTank] * _scoreTank[typeTank];
}


ScoreManager::ScoreManager()
{
	_scoreTank[0] = SCORE_MEDIUM_TANK;
	_scoreTank[1] = SCORE_LIGHT_TANK;
	_scoreTank[2] = SCORE_HEAVY_TANK;
	_scoreTank[3] = SCORE_SUPER_HEAVY_TANK;
	_scorePowerUp = SCORE_POWER_UP;
	renewValue();
	_playerScore = 0;
	string line;
	ifstream myfile("Resource\\Other\\highscore.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			_highScore << std::stoi(line);
		}
		myfile.close();
	}
}


ScoreManager::~ScoreManager()
{
}
