#include "Map.h"
#include "GameState.h"
#include "MediumTank.h"
#include "HeavyTank.h"
#include "SuperHeavyTank.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "Water.h"
#include "Trees.h"
#include "Ice.h"
#include "StageManager.h"
#include "LightTank.h"
#include "SteelWall.h"
#include "GameSound.h"

Map::Map(LPD3DXSPRITE spriteHandler)
{
	//init rectangleRespawn
	_rectangleEnemyRespawn = new vector<MyRectangle*>;
	_playerRespawnPos = new vector<MyRectangle*>;
	for (int i = 0; i < NUM_RESPAWN_POS;i++)
	{
		_rectangleEnemyRespawn->push_back(new MyRectangle(POS_RESPAWN_Y, POS_RESPAWN_X + i*DISTANCE_RESPAWN_POS_X, SPRITE_WIDTH, SPRITE_WIDTH, 0, 0));
	}	
	for (int i = 0; i < NUM_RESPAWN_POS - 1; i++)
	{
		if (i == 0)
		{
			_playerRespawnPos->push_back(new MyRectangle(DEFAULT_PLAYER_POSITION_Y, DEFAULT_PLAYER_POSITION_X, SPRITE_WIDTH, SPRITE_HEIGHT));
		}
		else if (i == 1)
		{
			_playerRespawnPos->push_back(new MyRectangle(DEFAULT_PLAYER_POSITION_Y, DEFAULT_PLAYER_POSITION_X_2, SPRITE_WIDTH, SPRITE_HEIGHT));
		}
	}
	_spriteHandler = spriteHandler;
	_spriteHandler->GetDevice(&_d3ddev);
	_text = new Text(_spriteHandler);
	_spriteItemManager = new SpriteMapItemMagager(_spriteHandler);
	_powerUpItem = new PowerUp(_spriteItemManager->getPowerUpItem(),_text);
	_respawnEffect = _spriteItemManager->getRespawnSprite();
	_eagle = new Eagle(_spriteItemManager->getEagleSprite(), getPositionFromMapMatrix(POS_EAGLE_IN_MATRIX_X, POS_EAGLE_IN_MATRIX_Y));
	_player = new PlayerTank(_spriteHandler);
	_listEnemy = new vector<Enemy*>;
	_listEnemyOnMap = new vector<Enemy*>;
	_mapMatrix = new int*[NUM_ROW_TILE];
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		_mapMatrix[i] = new int[NUM_COLUMN_TILE];
	}
	BulletManager::getInstance();
	EffectManager::getInstance(_spriteHandler);
	changeStage();
}

//----------------------------------
//dùng để chuyển từ stage này sang stage khác; reset một số thuộc tính về giá trị mặc định; 
//đọc file map và lấy các thông tin cần thiết như ma trận map, số lượng tank địch, ..; 
//tạo danh sách tank địch sẽ xuất hiện trên map, tạo danh sách các đối tượng tĩnh như gạch, thép, 
//rừng, ..; đưa ma trận map vào cho _player để hỗ trợ xét va chạm
//----------------------------------
void Map::changeStage()
{
	//
	_listStaticObject = new vector<vector<StaticObject*>>;
	_posGameOverText = POS_START_GAMEOVER;
	_delaytimeReSpawn = DEFINE_ZERO_VALUE;
	_delayEndStage = DELAY_TIME_END_PLAYING_STATE;
	_isPrepareRespawn = false;
	_maxEnemy = MAX_ENEMY;
	_numEnemy = DEFINE_ZERO_VALUE;
	_delayFreeze = DELAY_FREEZE_TIME;
	_isFreeze = false;
	//
	int numOfTypeEnemy[NUM_TYPE_ENEMY];
	string orderAppear;
	string stringLine;
	int tempMaxEnemy;
	if (!GetFileMap())
		return;
	getline(_mapFile, stringLine);
	tempMaxEnemy = std::stoi(stringLine);
	_maxEnemy = tempMaxEnemy;
	for (int i = 0; i < NUM_TYPE_ENEMY;i++)
	{
		getline(_mapFile, stringLine);
		numOfTypeEnemy[i] = std::stoi(stringLine);
	}
	getline(_mapFile, stringLine);
	orderAppear = stringLine;
	//read matrix map
	int i, j;
	i = 0;
	while (!_mapFile.eof())
	{
		j = 0;
		getline(_mapFile, stringLine);
		stringstream ss(stringLine);
		string token;
		while (getline(ss, token, ','))
		{
			_mapMatrix[i][j] = std::stoi(token);
			j++;
		}
		i++;
	}
	InitStaticObject();
	_mapFile.close();
	_player->InitMapData(_mapMatrix, _listStaticObject);
	InitListEnemy(numOfTypeEnemy,orderAppear);
	_powerUpItem->setmap(_mapMatrix);
}

//---------------------------------------
//dựa vào ma trận map để tạo ra các đối tượng tĩnh như gạch, thép, rừng,..;
//--------------------------------------
void Map::InitStaticObject()
{
	vector<StaticObject*> temp[MAP_NUM_OF_TYPE_OBJ];
	int type;
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		for (short j = 0; j < NUM_COLUMN_TILE; j++)
		{
			type = _mapMatrix[i][j] % 100;

			if (type == ID_BRICKWALL_0 || type == ID_BRICKWALL_1 || type == ID_BRICKWALL_10 || type == ID_BRICKWALL_11)
				temp[type].push_back(new BrickWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if(type == ID_STEELWALL_2 || type == ID_STEELWALL_3 || type == ID_STEELWALL_12 || type == ID_STEELWALL_13)
				temp[type].push_back(new SteelWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if (type == ID_WATER_4 || type == ID_WATER_5 || type == ID_WATER_14 || type == ID_WATER_15)
				temp[type].push_back(new Water(_spriteItemManager->getWater(), type, getPositionFromMapMatrix(i, j)));
			if (type == ID_TREES_6 || type == ID_TREES_7 || type == ID_TREES_16 || type == ID_TREES_17)
				temp[type].push_back(new Trees(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if (type == ID_ICE_8 || type == ID_ICE_9 || type == ID_ICE_18 || type == ID_ICE_19)
				temp[type].push_back(new Ice(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
		}
	}
	for (int i = 0; i < MAP_NUM_OF_TYPE_OBJ;i++)
		_listStaticObject->push_back(temp[i]);
}

//---------------------------------------
// tạo ra danh sách các tank địch sẽ xuất hiện trong stage tiếp 
//--------------------------------------
void Map::InitListEnemy(int numOfEnemy[], string order)
{
	//numOfEnemy[]
	//	0 - medium tank
	//	1 - light tank
	//	2 - heavy  tank
	//	3 - super heavy tank
	//order - Thu tu xuat hien cac loai tank 

	float distance = 0.0f;
	bool isBonusTank;
	vector<MediumTank*>* listMedium = new vector<MediumTank*>;
	vector<LightTank*>* listLight = new vector<LightTank*>;
	vector<HeavyTank*>* listHeavy = new vector<HeavyTank*>;
	vector<SuperHeavyTank*>* listSuper = new vector<SuperHeavyTank*>;
	for (int i = 0; i < _maxEnemy; i++)
	{
		isBonusTank = false;
		if (i == 3 || i == 10 || i == 17)
		{
			//set tank has powerup
			isBonusTank = true;
		}
		if (distance > MAX_RESPAWN_POS_X)
			distance = 0.0f;
		if(numOfEnemy[ID_MEDIUM_TANK] > 0)
		{
			MediumTank* temp;
			temp = new MediumTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y), isBonusTank);
			numOfEnemy[ID_MEDIUM_TANK] -= 1;
			temp->InitMapData(_mapMatrix, _listStaticObject);
			listMedium->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if(numOfEnemy[ID_LIGHT_TANK] > 0)
		{
			LightTank* temp;
			temp = new LightTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y), isBonusTank);
			numOfEnemy[ID_LIGHT_TANK] -= 1;
			temp->InitMapData(_mapMatrix, _listStaticObject);
			listLight->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if (numOfEnemy[ID_HEAVY_TANK] > 0)
		{
			HeavyTank* temp;
			temp = new HeavyTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y), isBonusTank);
			numOfEnemy[ID_HEAVY_TANK] -= 1;
			temp->InitMapData(_mapMatrix, _listStaticObject);
			listHeavy->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if (numOfEnemy[ID_SUPER_HEAVY_TANK] > 0)
		{
			SuperHeavyTank* temp;
			temp = new SuperHeavyTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y), isBonusTank);
			numOfEnemy[ID_SUPER_HEAVY_TANK] -= 1;
			temp->InitMapData(_mapMatrix, _listStaticObject);
			listSuper->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
		}
	}
	int i = 0;
	int n;
	while(i<NUM_TYPE_ENEMY)
	{
		switch (order[i] - '0')
		{
			case ID_MEDIUM_TANK:
			{
				n = listMedium->size();
				for (int j = 0; j < n;j++)
				{
					_listEnemy->push_back(listMedium->front());
					listMedium->erase(listMedium->begin());
				}		
				delete listMedium;
				break;
			}
			case ID_LIGHT_TANK:
			{
				n = listLight->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listLight->front());
					listLight->erase(listLight->begin());
				}
				delete listLight;
				break;
			}
			case ID_HEAVY_TANK:
			{
				n = listHeavy->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listHeavy->front());
					listHeavy->erase(listHeavy->begin());
				}
				delete listHeavy;
				break;
			}
			case ID_SUPER_HEAVY_TANK:
			{
				n = listSuper->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listSuper->front());
					listSuper->erase(listSuper->begin());
				}
				delete listSuper;
				break;
			}
		}
		i++;
	}
}

//---------------------------------------
//Mở file map định dạng txt
//--------------------------------------
bool Map::GetFileMap()
{
	string mapPath = MAP_PATH + std::to_string(StageManager::getInstance()->getStage()) + MAP_FILE_EXTENSION;
	_mapFile.open(mapPath, ios::in);
	if (_mapFile.fail())
	{
		WARNING_BOX(WARNING_MAP_FILE_NOT_FOUND);
		return false;
	}
	return true;
}


void Map::Draw()
{
	_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, COLOR_GREY, 1.0f, 0);
	drawRightMenu();	
	drawMap();
	drawEagle();
	BulletManager::getInstance()->Draw();
	drawIce();
	drawPlayer();
	drawEnemy();
	drawTrees();
	drawPowerUp();
	EffectManager::getInstance(0)->Draw();
	if (_player->getLife() < 0 || _eagle->getEagleStatus() == EAGLE_STATUS::DEAD)
	{
		_text->drawText("GAME\nOVER", _posGameOverText, COLOR_RED, 30, DT_CENTER, 0, 2);
	}
}

//---------------------------------------
// duyệt _listStaticObject và vẽ các đối tượng thuộc loại rừng lên map 
//--------------------------------------
void Map::drawTrees()
{
	int n = _listStaticObject->size();
	for (int i = 0; i < n; i++)
	{
		if (_listStaticObject->at(i).size() != 0)
		{
			if (i != ID_TREES_6 && i != ID_TREES_7 && i != ID_TREES_16 && i != ID_TREES_17)
				continue;
			int m = _listStaticObject->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_listStaticObject->at(i).at(j) != NULL)
					_listStaticObject->at(i).at(j)->Draw();
			}
		}
	}
}

//---------------------------------------
// duyệt _listStaticObject và vẽ các đối tượng thuộc loại băng lên map
//--------------------------------------
void Map::drawIce()
{
	int n = _listStaticObject->size();
	for (int i = 0; i < n; i++)
	{
		if (_listStaticObject->at(i).size() != 0)
		{
			if (i != ID_ICE_8 && i != ID_ICE_9 && i != ID_ICE_18 && i != ID_ICE_19)
				continue;
			int m = _listStaticObject->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_listStaticObject->at(i).at(j) != NULL)
					_listStaticObject->at(i).at(j)->Draw();
			}
		}
	}
}

//---------------------------------------
//vẽ các đối tượng tĩnh trong _listStaticObject lên map game, 
//nơi nào không có đối tượng thì vẽ nền màu đen. Nhưng có điều 
//đặc biệt là trong hàm này ta chỉ vẻ gạch, thép, sông. Rừng và 
//băng sẽ được vẽ sau vì độ sâu của nền của các đối tượng này khác nhau. 
//--------------------------------------
void Map::drawMap()
{
	//ve map
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		for (short j = 0; j < NUM_COLUMN_TILE; j++)
		{
			int type = _mapMatrix[i][j] % 100;
			if (type == ID_TREES_6 || type == ID_TREES_7 || type == ID_TREES_16 || type == ID_TREES_17 || _mapMatrix[i][j] == -1)
			{
				_spriteItemManager->getBackGround()->Render(0, 0, getPositionFromMapMatrix(i, j));
			}
		}
	}
	int n = _listStaticObject->size();
	for (int i = 0; i < n; i++)
	{
		if (_listStaticObject->at(i).size() != 0)
		{
			if (i == ID_TREES_6 || i == ID_TREES_7 || i == ID_TREES_16 || i == ID_TREES_17 ||
				i == ID_ICE_8 || i == ID_ICE_9 || i == ID_ICE_18 || i == ID_ICE_19)
				continue;
			int m = _listStaticObject->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_listStaticObject->at(i).at(j) != NULL)
					_listStaticObject->at(i).at(j)->Draw();
			}
		}
	}
	
}

//---------------------------------------
// vẽ căn cứ lên map
//--------------------------------------
void Map::drawEagle()
{
	_eagle->Draw();
}

//---------------------------------------
// vẽ tank của người chơi lên map
//--------------------------------------
void Map::drawPlayer()
{
	_player->Draw();
}

//---------------------------------------
// vẽ power lên màn hình nếu nó được kích hoạt bởi việc bắn chết tank địch có nháy đỏ
//--------------------------------------
void Map::drawPowerUp()
{
	_powerUpItem->Draw();
}

//---------------------------------------
// Vẽ các xe tank địch lên map. Ở những xe tank địch chuẩn bị xuất hiện sẽ vẽ thêm hiệu ứng nhấp nháy 
//--------------------------------------
void Map::drawEnemy()
{
	if (_isPrepareRespawn)
	{
		if(_delaytimeReSpawn % 100 == 0)
		{
			_respawnEffect->Render(_listEnemy->front()->getLeft(), _listEnemy->front()->getTop());
			_respawnEffect->Next();
		}
	}
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->Draw();
	}
}

//---------------------------------------
// vẽ số lượng tank địch còn lại chưa xuất hiện trên map. 
// Vẽ số thứ tự của stage hiện tại, số mạng còn lại của người chơi. 
//--------------------------------------
void Map::drawRightMenu()
{
	///////////Draw khung enemy goc phai
	float x, y;
	int num_enemy = _maxEnemy - _numEnemy;
	for (int i = 0; i < num_enemy; i++)
	{
		if (i % 2 == 0)
		{
			x = POS_LIST_ENEMY_ICON_TOP_LEFT_X;
		}
		else
		{
			x = POS_LIST_ENEMY_ICON_TOP_LEFT_X + (TILE_WIDTH * 2);
		}
		y = POS_LIST_ENEMY_ICON_TOP_LEFT_Y + (TILE_HEIGHT * 2)*(i / 2);
		_spriteItemManager->getEnemyIcon()->Render(0, 0, D3DXVECTOR3(x, y, 0.0f));
	}

	//Draw dem so mang
	_spriteItemManager->getTankLifeIcon()->Render(0, 0, POS_LIFE_IMAGE);
	//Draw so thu tu state hien tai
	_spriteItemManager->getFlagIcon()->Render(0, 0, POS_FLAG_LIFE_IMAGE);
	//Ve so
	_text->drawText (to_string(StageManager::getInstance()->getStage()),POS_NUM_LEVEL,COLOR_BLACK,20);
	int life = _player->getLife();
	if (life < 0)
		life = 0;
	_text->drawText(to_string(life), POS_NUM_LIFE, COLOR_BLACK, 17);
}

//---------------------------------------

//--------------------------------------
void Map::Update()
{
	//Cập nhật tank người chơi
	if (_eagle->getEagleStatus() == EAGLE_STATUS::LIVE)
	{
		_player->Update();
	}

	//Cập nhật tank địch
	updateEnemy();

	//Cập nhật đạn
	BulletManager::getInstance()->Update();

	//Xét va chạm giữa tank người chơi và căn cứ
	CollisionManager::CollisionPreventMove(_player, _eagle);

	//Xét va chạm giữa tank địch và căn cứ
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		bool isCollided = CollisionManager::CollisionPreventMove(_listEnemyOnMap->at(i), _eagle);
		if (isCollided)
			break;
	}

	//Xét va chạm giữa các xe tank địch với nhau
	bool isCollision;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = i+1; j < n; j++)
		{
	
				isCollision = CollisionManager::CollisionEnemy(_listEnemyOnMap->at(i), _listEnemyOnMap->at(j));
				if (isCollision)
					break;
			
		}
	}

	//Xét va chạm giữa các xe tank địch với tank người chơi
	for (int i = 0; i < n; i++)
	{
		CollisionManager::CollisionChangeDirection(_player, _listEnemyOnMap->at(i));
	}

	//Xét va chạm giữa đạn với tank địch với tank người chơi
	if (_eagle->getEagleStatus() == EAGLE_STATUS::LIVE)
	{
		if (n == 0)
			BulletManager::getInstance()->UpdateCollisionWithDynamicObject(_player, _powerUpItem, _eagle);
		for (int i = 0; i < n; i++)
		{
			BulletManager::getInstance()->UpdateCollisionWithDynamicObject(_player, _powerUpItem, _eagle, _listEnemyOnMap->at(i));
		}

	}

	//Xét va chạm giữa tank người chơi và powerup item
	if(_powerUpItem->IsEnable())
	{
		CollisionManager::CollisionWithItem(_player, _powerUpItem);
	}

	//Hồi sinh tank của người chơi
	if (_player->_isTerminated)
	{
		if (_player->getLife() > 0)
		{
			int pos = CollisionManager::FindRespawnPosition(_playerRespawnPos, DEFINE_ZERO_VALUE, _listEnemyOnMap);
			if (pos == 0)
			{
				_player->Respawn(DEFAULT_PLAYER_POSITION_X, DEFAULT_PLAYER_POSITION_Y);
			}
			else if (pos == 1)
			{
				_player->Respawn(DEFAULT_PLAYER_POSITION_X_2, DEFAULT_PLAYER_POSITION_Y);
			}
			else
			{
				_player->setPositionX(DEFINE_ZERO_VALUE);
				_player->setPositionY(DEFAULT_PLAYER_POSITION_Y);
			}

		}
		else
		{
			_player->setLife(-1);
			_player->setPositionX(DEFINE_ZERO_VALUE);
			_player->setPositionY(DEFINE_ZERO_VALUE);
		}
	}
	updatePowerItem();
	ClearDestroyedEnemy();
	checkEndGame();
}

//---------------------------------------
//cập nhật các đối tượng tank địch trên map. Nếu số lượng tank địch trên map < 4 
//thì cho thêm tank địch xuất hiện và đảm bảo số lượng tank địch luôn <= 4. 
//--------------------------------------
void Map::updateEnemy()
{
	if (_listEnemyOnMap->size() < MAX_ENEMY_ONE_TIME && _listEnemy->size() >= 1)
	{
		if (_numEnemy == 0)
		{
			respawnAfter(DELAY_TIME_RESPAWN_1000);
		}
		else
		{
			respawnAfter(DELAY_TIME_RESPAWN_4000);
		}
	}
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->Update();
	}
}

//---------------------------------------
//kiểm tra vị trí sắp xuất hiện của tank địch có đối tượng nào đang đứng ở đó không, 
//nếu có thì chuyển hướng xuất hiện qua 1 trong 2 vị trí còn lại, nếu không thì xuất hiện bình thường
//--------------------------------------
bool Map::checkCollisionRespawnArea()
{
	int index;
	for (index = 0; index < NUM_RESPAWN_POS; index++)	//Lay vi tri chuan bi xuat hien
	{
		if(_rectangleEnemyRespawn->at(index)->getLeft() == _listEnemy->front()->getLeft())
			break;
	}
	int colli = CollisionManager::FindRespawnPosition(_rectangleEnemyRespawn, index, _player, _listEnemyOnMap); //kiem tra co bị va cham tại vi tri xuat hien hay khong, tra ve vi tri co the xuat hien
	if ( colli != index)
	{
		if(colli != -1)
		{
			_listEnemy->front()->setPositionX(_rectangleEnemyRespawn->at(colli)->getLeft());
			return false;
		}
		return true;
	}
	return false;
}

//---------------------------------------
// phân phối thời gian xuất hiện tank định một cách hợp lí. 
//Nếu powerup Freeze đang được kích hoạt thì cho tank địch chuẩn bị xuất 
//hiện cũng bị ảnh hưởng bới powerup này. Nếu tank địch thứ 11 hoặc 
//18 xuất hiện mà powerup vẫn chưa ăn thì powerup sẽ biến mất.
//--------------------------------------
void Map::respawnAfter(int delaytime)
{
	_delaytimeReSpawn += 50;
	if(delaytime == DELAY_TIME_RESPAWN_1000)
	{
		_isPrepareRespawn = true;
	}
	else
	{
		if(_delaytimeReSpawn >(DELAY_TIME_RESPAWN_4000 - DELAY_TIME_RESPAWN_1000))
		{
			_isPrepareRespawn = true;
		}
	}
	if (_delaytimeReSpawn > delaytime)
	{

		_isPrepareRespawn = false;
		_delaytimeReSpawn = 0;
		if(checkCollisionRespawnArea())
		{
			return;
		}
		if(_isFreeze)
		{
			_listEnemy->front()->ActivateFreeze();
		}
		_listEnemyOnMap->push_back(_listEnemy->front());
		_listEnemy->erase(_listEnemy->begin());
		_numEnemy++;
		if (_numEnemy == 11 || _numEnemy == 18)
		{
			if (_powerUpItem->IsEnable())
			{
				_powerUpItem->disablePowerUp();
			}
		}
	}
}

//---------------------------------------
// Nếu powerup bị người chơi ăn thì kích hoạt chức năng của powerup. 
//Tuỳ theo từng loại powerup mà có các chức năng khác nhau. 
//Nếu chức năng đóng băng di chuyển tank địch đã được kích hoạt thì kiểm tra thời gian đóng 
//băng đã hết chưa để đưa tank địch về lại trạng thái bình thường.
//--------------------------------------
void Map::updatePowerItem()
{
	if (_isFreeze)
	{
		if (GameTime::DelayTime(_delayFreeze))
		{
			_delayFreeze = DELAY_FREEZE_TIME;
			_isFreeze = false;
			UnFreezeEnemyOnMap();
		}
		return;
	}
	if (_powerUpItem->IsEnable())
	{
		if (_powerUpItem->IsEaten())
		{

			if (_powerUpItem->getType() == ID_POWER_FREEZE_TIME)
			{
				_isFreeze = true;
				FreezeEnemyOnMap();
			}
			if (_powerUpItem->getType() == ID_POWER_BOMB)
			{
				ClearEnemyOnMap();
			}
			if (_powerUpItem->getType() == ID_POWER_SHEILD)
			{
				_player->ActivateShield(true);
			}
			if (_powerUpItem->getType() == ID_POWER_EXTRA_LIFE)
			{
				_player->addLife();
			}
			if (_powerUpItem->getType() == ID_POWER_STAR)
			{
				_player->PlayerPromoted();
			}
			_powerUpItem->disablePowerUp();
		}
	}
}

//---------------------------------------
// kiểm tra kết thúc game. Nếu người chơi hết mạng hoặc căn cứ bị phá huỷ thì vẽ dòng chữ “GAMEOVER”, 
//game sẽ kết thúc sau màn ScoreState (ScoreState::get()->setEndAfter(true)). Nếu người chơi đã tiêu diệt 
//hết tank địch thì game sẽ chuyển tới stage StartingState sau màn ScoreState. Trước khi chuyển state, phải 
//gọi hàm CleanStage() để xoá các đối tượng của stage vừa mới chơi xong
//--------------------------------------
void Map::checkEndGame()
{
	if (_player->getLife() < 0 || _eagle->getEagleStatus() == EAGLE_STATUS::DEAD)
	{
		if (_posGameOverText.y > POS_END_GAMEOVER_Y)
		{
			_posGameOverText.y -= 10;
		}
		if (GameTime::DelayTime(_delayEndStage))
		{
			CleanStage();
			ScoreState::get()->setEndAfter(true);
			GameState::switchState(ScoreState::get());	
		}
		return;
	}

  	if (_numEnemy == _maxEnemy && _listEnemyOnMap->size() == 0)
	{
		if (GameTime::DelayTime(_delayEndStage))
		{
			CleanStage();
			StageManager::getInstance()->nextStage();
			if (StageManager::getInstance()->getStage() <= DEFAULT_MAX_STAGE)
			{
				changeStage();
			}
			GameState::switchState(ScoreState::get());
		}
	}

}

//---------------------------------------
//trả về _listStaticObject
//--------------------------------------
vector<vector<StaticObject*>>* Map::getStaticObject()
{
	return _listStaticObject;
}

Eagle * Map::getEagleObject()
{
	return _eagle;
}

Map::~Map()
{
}

int** Map::getMapMatrix()
{
	return this->_mapMatrix;
}

//---------------------------------------
//đưa vào vị trí trong ma trận map để lấy ra vi trí thực trên màn hình chơi.
//--------------------------------------
D3DXVECTOR3 Map::getPositionFromMapMatrix(int row, int column)
{
	D3DXVECTOR3 vector;
	vector.x = column*TILE_WIDTH + POS_MAP_TOP_LEFT_X;
	vector.y = row*TILE_HEIGHT + POS_MAP_TOP_LEFT_Y;
	vector.z = 0.0f;
	return vector;
}

//---------------------------------------
//đưa vào toạ độ trên màn hình chơi để lấy ra vị trí trong ma trận map
//--------------------------------------
D3DXVECTOR2 Map::getPositionObjectInMapMatrix(int x, int y)
{
	D3DXVECTOR2 position;
	position.x = (x - POS_MAP_TOP_LEFT_X) / TILE_WIDTH;
	position.y = (y - POS_MAP_TOP_LEFT_Y) / TILE_HEIGHT;
	return position;
}

//---------------------------------------
// Vì khi xét va chạm không huỷ liền đối tượng mà chỉ xét thuộc tính _isTerminated = true 
//vậy nên cần có hàm này để xoá các đối tượng bị terminated. 
//--------------------------------------
void Map::ClearDestroyedEnemy()
{
	for (vector<Enemy*>::iterator i = _listEnemyOnMap->begin(); i != _listEnemyOnMap->end();)
	{
		if ((*i)->_isTerminated)
		{
			delete *i;
			*i = NULL;
			i = _listEnemyOnMap->erase(i);
		}
		else
		{
			i++;
		}
	}
}

//---------------------------------------
// Sau khi hoàn thành 1 stage, trước khi chuyển qua ScoreState thì cần phải dọn dẹp 
// các đối tượng tĩnh chưa bị phá huỷ trên map để nạp vào các đối tượng tĩnh của stage sau, đó chính là mục đích của hàm này.
//--------------------------------------
void Map::ClearStaticObject()
{
	int n = _listStaticObject->size();
	for (int i = 0; i < n; i++)
	{
		if (_listStaticObject->at(i).size() != 0)
		{
			int m = _listStaticObject->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_listStaticObject->at(i).at(j) != NULL)
				{
					delete _listStaticObject->at(i).at(j);
					_listStaticObject->at(i).at(j) = NULL;
				}
			}
		}
	}
	delete _listStaticObject;
	_listStaticObject = NULL;
}

//---------------------------------------
// nếu người chơi bị thua cuộc, danh sách tank địch cần phải được xoá để nạp lại danh sách mới chuẩn bị cho người chơi sau. 
//--------------------------------------
void Map::ClearDynamicObject()
{
	int n = _listEnemy->size();
	for (int i = 0; i < n;i++)
	{
		_listEnemy->erase(_listEnemy->begin());
	}
	n = _listEnemyOnMap->size();
	{
		for (int i = 0; i < n;i++)
		{
			_listEnemyOnMap->erase(_listEnemyOnMap->begin());
		}
	}
}

//---------------------------------------
// Đưa tank của người chơi về vị trí mặc định
//--------------------------------------
void Map::SetDefaultPositionPlayer()
{
	_player->setPositionX(DEFAULT_PLAYER_POSITION_X);
	_player->setPositionY(DEFAULT_PLAYER_POSITION_Y);
	_player->SetDirection(MoveDirection::UP);
	_player->ActivateShield();
	
}

//---------------------------------------
// Huỷ tất cả các đối tượng tank địch hiện có trên map
//--------------------------------------
void Map::ClearEnemyOnMap()
{
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->_isTerminated = true;
		D3DXVECTOR2 pos(_listEnemyOnMap->at(i)->getLeft(), _listEnemyOnMap->at(i)->getTop());
		EffectManager::getInstance()->AddDestroyEffect(pos);
	}
	GameSound::getInstance()->Play(ID_SOUND_TANK_EXPLODE);
}

//---------------------------------------
// “Đóng băng”(ngưng di chuyển) tất cả các đối tượng tank địch hiện có trên map.
//--------------------------------------
void Map::FreezeEnemyOnMap()
{
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->ActivateFreeze();
	}
}

//---------------------------------------
// đưa tank địch về trạng thái di chuyển bình thường.
//--------------------------------------
void Map::UnFreezeEnemyOnMap()
{
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->DeactivateFreeze();
	}
}

//---------------------------------------

//--------------------------------------
void Map::CleanStage()
{
	ClearStaticObject();
	ClearDynamicObject();
	SetDefaultPositionPlayer();
	BulletManager::getInstance()->ClearAllBullet();
	_powerUpItem->clearPowerUp();
	_eagle->setEagleStatus(EAGLE_STATUS::LIVE);
	_player->TurnOffSound();
}

//---------------------------------------
// Dọn dẹp map game để chuẩn bị load map sau.
//--------------------------------------
void Map::reset()
{
	_player->reset();
	changeStage();
}
