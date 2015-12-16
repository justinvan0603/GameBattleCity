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

//----------------------------------
//	Cong diem khi ban chet tank theo tung loai
//----------------------------------
void ScoreManager::addKillTankScore(int typeTank)
{
	_playerScore += _scoreTank[typeTank];
	_numTank[typeTank]++;
}

//----------------------------------
// Cong diem khi an powerUp
//----------------------------------
void ScoreManager::addPowerUpScore()
{
	_playerScore += _scorePowerUp;
}

//----------------------------------
// Lay so luong tank da bi ban chet theo loai
//----------------------------------
int ScoreManager::getNumTank(int typeTank)
{
	return _numTank[typeTank];
}

//----------------------------------
// Lay so luong tank bi ban chet
//----------------------------------
int ScoreManager::getNumTank()
{
	int temp = 0;
	for (int i = 0; i < NUM_TYPE_ENEMY;i++)
	{
		temp += _numTank[i];
	}
	return temp;
}

//----------------------------------
// Khoi tao lai gia tri ban dau khi qua stage moi
//----------------------------------
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

//----------------------------------
// Lay diem dat duoc theo tung loai tank
//----------------------------------
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
	//Doc file lay diem cao nhat
	string line;
	fstream _mapFile;
	string scoreFilePath = HI_SCORE_FILE_PATH;
	_mapFile.open(scoreFilePath, ios::in);
	if (!_mapFile.fail())
	{
		while (!_mapFile.eof())
		{
			getline(_mapFile, line);
			_highScore = std::stoi(line);
		}
	}
	_mapFile.close();
}


ScoreManager::~ScoreManager()
{
}
