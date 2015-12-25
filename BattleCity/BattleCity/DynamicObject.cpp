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
//Muc dich tao ra ham nay la de lay chinh xac nhung object co kha nang va cham voi object dong nham tiet kiem chi phi
//Thay vi phai for kiem tra toan bo object tinh tren map se ton rat nhieu chi phi
void DynamicObject::FindNearbyObject()
{

	int currentObjectColumn = (_left - POS_MAP_TOP_LEFT_X)/ TILE_WIDTH;	//Tinh vi tri (column)cua object hien tai tren ma tran
	int currentObjectRow = (_top - POS_MAP_TOP_LEFT_Y) /TILE_HEIGHT;	//Tinh vi tri (row)cua object hien tai tren ma tran
	if (currentObjectRow > 52 || currentObjectColumn > 52 || currentObjectRow <0 || currentObjectColumn <0)	//Loai truong hop bi bug
		return;
	int nearbyObjectCountWidth;
	int nearbyObjectCountHeight;
	if (this->_id != ID_BULLET)	//Neu object dang xet la xe tank co kich thuoc 32x32 (4*4 tile)
	{
		if ((_left - POS_MAP_TOP_LEFT_X) % TILE_WIDTH == 0)	//Neu vi tri theo truc x cua object chia het cho kich thuoc 1 tile thi lay 4 object xung quanh
		{
			nearbyObjectCountWidth = 4;
		}
		else //Neu khong chia het nghia la object nam o khoang giao giua 2 tile thi phai lay 5 object xung quanh
		{
			nearbyObjectCountWidth = 5;
		}
		//Tuong tu nhu truc x
		if ((_top - POS_MAP_TOP_LEFT_Y) % TILE_HEIGHT == 0)
		{
			nearbyObjectCountHeight = 4;
		}
		else
		{
			nearbyObjectCountHeight = 5;
		}
	}
	else //Neu la dan thi lay 1 object xung quanh do dan co kich thuoc = 1 tile 
	{
		nearbyObjectCountHeight = nearbyObjectCountWidth = 1;
	}
	//Lay cac object tinh nam o canh tren va canh duoi cua object dong
	for (int i = currentObjectColumn - 1; i <= currentObjectColumn + nearbyObjectCountWidth; i++)
	{
		int value;
		if (i >= 0 && i < 52)
		{
			if (currentObjectRow - 1 >= 0)
			{
				value = _map[currentObjectRow-1][i];
				if (value != -1)
				{	//Kiem tra neu object tinh la trees, ice thi khong xet va cham
					if (value % 100 != ID_TREES_6 && value % 100 != ID_TREES_7 && value % 100 != ID_TREES_16 && value % 100 != ID_TREES_17 &&
						value % 100 != ID_ICE_8 && value % 100 != ID_ICE_9 && value % 100 != ID_ICE_18 && value % 100 != ID_ICE_19)
					{
						//Neu la dan thi khong lay water
						if (_id == ID_BULLET)
						{
							if (value % 100 != ID_WATER_4 && value % 100 != ID_WATER_5 && value % 100 != ID_WATER_14 && value % 100 != ID_WATER_15)
								_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
						}
						else
							_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
					}
				}
			}

			if (currentObjectRow + nearbyObjectCountHeight < 52)
			{
				value = _map[currentObjectRow + nearbyObjectCountHeight][i];
				if (value != -1)
				{
					if (value % 100 != ID_TREES_6 && value % 100 != ID_TREES_7 && value % 100 != ID_TREES_16 && value % 100 != ID_TREES_17 &&
						value % 100 != ID_ICE_8 && value % 100 != ID_ICE_9 && value % 100 != ID_ICE_18 && value % 100 != ID_ICE_19)
					{
						if (_id == ID_BULLET)
						{
							if (value % 100 != ID_WATER_4 && value % 100 != ID_WATER_5 && value % 100 != ID_WATER_14 && value % 100 != ID_WATER_15)
								_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
						}
						else
							_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
					}
					//_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
				}
			} 
		}
	}
	//Lay cac object tinh xung quanh object dong o 2 ben canh trai va phai
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
					if (value % 100 != ID_TREES_6 && value % 100 != ID_TREES_7 && value % 100 != ID_TREES_16 && value % 100 != ID_TREES_17 &&
						value % 100 != ID_ICE_8 && value % 100 != ID_ICE_9 && value % 100 != ID_ICE_18 && value % 100 != ID_ICE_19)
					{
						if (_id == ID_BULLET)
						{
							if (value % 100 != ID_WATER_4 && value % 100 != ID_WATER_5 && value % 100 != ID_WATER_14 && value % 100 != ID_WATER_15)
								_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
						}
						else
							_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
					}
				//	_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
				}
			}

			if (currentObjectColumn + nearbyObjectCountWidth < 52)
			{
				value = _map[i][currentObjectColumn + nearbyObjectCountWidth];
				if (value != -1)
				{
					if (value % 100 != ID_TREES_6 && value % 100 != ID_TREES_7 && value % 100 != ID_TREES_16 && value % 100 != ID_TREES_17 &&
						value % 100 != ID_ICE_8 && value % 100 != ID_ICE_9 && value % 100 != ID_ICE_18 && value % 100 != ID_ICE_19)
					{
						if (_id == ID_BULLET)
						{
							if (value % 100 != ID_WATER_4 && value % 100 != ID_WATER_5 && value % 100 != ID_WATER_14 && value % 100 != ID_WATER_15)
								_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
						}
						else
							_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
					}
					//_listCollisionObject.push_back((_listNearByObject)->at(value % 100).at(value / 100));
				}
			}
		}
	}
	
}
void DynamicObject::Update()
{
	_listCollisionObject.clear();
}
//Gan tham chieu ma tran map va list Object tinh cho doi tuong
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
//Random lay ra vi tri khac voi vi tri ban dau luc truyen vao
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
