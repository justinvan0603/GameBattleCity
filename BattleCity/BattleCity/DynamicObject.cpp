#include "DynamicObject.h"


DynamicObject::DynamicObject()
{
	_objectType = DYNAMIC_OBJECT;

}

MoveDirection DynamicObject::getCurrentMoveDirection()
{
	return this->_currentDirection;
}

void DynamicObject::setCurrentMoveDirection(MoveDirection direction)
{
	this->_currentDirection = direction;
	int vx, vy;

	if (this->_id == ID_LIGHT_TANK)
	{
		vx = DYNAMIC_OBJECT_HIGH_SPEED.x;
		vy = DYNAMIC_OBJECT_HIGH_SPEED.y;
	}
	else
	{
		vx = DYNAMIC_OBJECT_LOW_SPEED.x;
		vy = DYNAMIC_OBJECT_LOW_SPEED.y;
	}
	switch (_currentDirection)
	{
	case UP:
	{
		_vx = 0;
		_vy = -vy;
		break;
	}
	case LEFT:
	{
		_vy = 0;
		_vx = -vx;
		break;
	}
	case DOWN:
	{
		_vx = 0;
		_vy = vy;
		break;
	}
	case RIGHT:
	{
		_vy = 0;
		_vx = vx;
		break;
	}
	default:
		break;
	}
}
int DynamicObject::GetLevel()
{
	return this->_level;
}
void DynamicObject::FindNearbyObject()
{
	int currentObjectColumn = (_left - POS_MAP_TOP_LEFT_X)/ TILE_WIDTH;
	int currentObjectRow = (_top - POS_MAP_TOP_LEFT_Y) /TILE_HEIGHT;
	if (currentObjectRow > 52 || currentObjectColumn > 52)
		return;
	int nearbyObjectCountWidth;
	int nearbyObjectCountHeight;
	if (this->_id != ID_BULLET)
	{
		if ((_left - POS_MAP_TOP_LEFT_X) % TILE_WIDTH == 0)
		{
			nearbyObjectCountWidth = 4;
		}
		else
		{
			nearbyObjectCountWidth = 5;
		}

		if ((_top - POS_MAP_TOP_LEFT_Y) % TILE_HEIGHT == 0)
		{
			nearbyObjectCountHeight = 4;
		}
		else
		{
			nearbyObjectCountHeight = 5;
		}
	}
	else
	{
		nearbyObjectCountHeight = nearbyObjectCountWidth = 1;
	}

	for (int i = currentObjectColumn - 1; i <= currentObjectColumn + nearbyObjectCountWidth; i++)
	{
		int value;
		if (i >= 0 && i < 52)
		{
			if (currentObjectRow - 1 >= 0)
			{
				value = _map[currentObjectRow-1][i];
				if (value != -1)
				{
					if (value % 100 != 6 && value % 100 != 7 && value % 100 != 16 && value % 100 != 17 &&
						value % 100 != 8 && value % 100 != 9 && value % 100 != 18 && value % 100 != 19)
						_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
				}
			}

			if (currentObjectRow + nearbyObjectCountHeight < 52)
			{
				value = _map[currentObjectRow + nearbyObjectCountHeight][i];
				if (value != -1)
				{
					if (value % 100 != 6 && value % 100 != 7 && value % 100 != 16 && value % 100 != 17 &&
						value % 100 != 8 && value % 100 != 9 && value % 100 != 18 && value % 100 != 19)
		
					_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
				}
			} 
		}
	}

	for (int i = currentObjectRow; i < currentObjectRow + nearbyObjectCountHeight; i++)
	{
		int value;
		if (i >= 0 && i < 52)
		{
			if (currentObjectColumn - 1 >= 0)
			{
				value = _map[i][currentObjectColumn - 1];
				if (value != -1)
				{
					if (value % 100 != 6 && value % 100 != 7 && value % 100 != 16 && value % 100 != 17 &&
						value % 100 != 8 && value % 100 != 9 && value % 100 != 18 && value % 100 != 19)

					_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
				}
			}

			if (currentObjectColumn + nearbyObjectCountWidth < 52)
			{
				value = _map[i][currentObjectColumn + nearbyObjectCountWidth];
				if (value != -1)
				{
					if (value % 100 != 6 && value % 100 != 7 && value % 100 != 16 && value % 100 != 17 &&
						value % 100 != 8 && value % 100 != 9 && value % 100 != 18 && value % 100 != 19)
			
					_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
				}
			}
		}
	}
	
}
void DynamicObject::Update()
{
	_listCollisionObject.clear();
}

void DynamicObject::InitMapData(int** map, vector<vector<StaticObject*>>* listNearByObject)
{
	_map = map;
	_listNearByObject = listNearByObject;
}

void DynamicObject::InvertDirection()
{
	switch (_currentDirection)
	{
		case UP:
		{
			setCurrentMoveDirection(DOWN);
			break;
		}
		case LEFT:
		{
			setCurrentMoveDirection(RIGHT);
			break;
		}
		case DOWN:
		{
			setCurrentMoveDirection(UP);
			break;
		}
		case RIGHT:
		{
			setCurrentMoveDirection(LEFT);
			break;
		}
	}
}
MoveDirection DynamicObject::RandomDirection()
{
	srand(time(0));
	return static_cast<MoveDirection>(rand() % NUM_OF_DIRECTION);
}
void DynamicObject::RandomChangeDirection()
{
	MoveDirection newDirection = _currentDirection;
	srand(time(0));
	while (newDirection == _currentDirection)
	{
		
		newDirection = static_cast<MoveDirection>(rand() % NUM_OF_DIRECTION);
	}
	_currentDirection = newDirection;
	//setCurrentMoveDirection(newDirection);
}
DynamicObject::~DynamicObject()
{
	//for (int i = 0; i < NUM_OF_DIRECTION; i++)
///	{
	//	delete this->_listSprite[i];
	//}
	//delete this->_listSprite;
}
