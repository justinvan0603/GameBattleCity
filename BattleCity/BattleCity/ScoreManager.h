#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__
class ScoreManager
{
public:
	static ScoreManager* getInstance();
	int CalculateScore(int type, int num);
	void addScore(int score);
	int getScore();
	int getHighScore();
private:
	ScoreManager();
	~ScoreManager();
	static ScoreManager* _instance;
	int _score;
	int _highScore;
	int _scoreTank[4];
};
#endif
 

