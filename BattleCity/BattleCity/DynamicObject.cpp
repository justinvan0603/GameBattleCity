#include "DynamicObject.h"


DynamicObject::DynamicObject()
{
	_objectType = DYNAMIC_OBJECT;

}

MoveDirection DynamicObject::getCurrentMoveDirection()
{
	return this->_currentDirection;
}

void DynamicObject::FindNearbyObject()
{
//	int currentObjectColumn = (_left -    / TILE_WIDTH;
	int currentObjectRow = _top / TILE_HEIGHT;
	int nearbyObjectCountWidth;
	int nearbyObjectCountHeight;
	if (_left % TILE_WIDTH == 0)
	{
		nearbyObjectCountWidth = 4;
	}
	else
	{
		nearbyObjectCountWidth = 5;
	}
	if (_top % TILE_HEIGHT == 0)
	{
		nearbyObjectCountHeight = 4;
	}
	else
	{
		nearbyObjectCountHeight = 5;
	}
	//for (int i = currentObjectColumn; i < currentObjectColumn + nearbyObjectCountWidth; i++)
	//{

	//	int value = (*_map)[currentObjectRow - 1][i];
	//	if (value != -1)
	//	{
	//		_listCollisionObject.push_back(_listStaticObject[value % 100][value / 100]);
	//	}
	//	value = (*_map)[currentObjectRow + nearbyObjectCountHeight][i];
	//	if (value != -1)
	//	{
	//		_listCollisionObject.push_back(_listStaticObject[value % 100][value / 100]);
	//	}
	//}

	//for (int i = currentObjectRow; i < currentObjectRow + nearbyObjectCountHeight; i++)
	//{
	//	int value = (*_map)[i][currentObjectColumn - 1];
	//	if (value != -1)
	//	{
	//		_listCollisionObject.push_back(_listStaticObject[value % 100][value / 100]);
	//	}
	//	value = (*_map)[i][currentObjectColumn + nearbyObjectCountWidth];
	//	if (value != -1)
	//	{
	//		_listCollisionObject.push_back(_listStaticObject[value % 100][value / 100]);
	//	}
	//}

	//for (int i = currentObjectColumn; i < currentObjectColumn + nearbyObjectCountWidth; i++)
	//{
	//	int value = (*_map)[currentObjectRow - 1][i];
	//	if (value != -1 )
	//	{
	//		_listCollisionObject.push_back(_listNearByObject->at(value%100).at(value/100));
	//	}
	//	value = (*_map)[currentObjectRow + nearbyObjectCountHeight][i];
	//	if (value != -1)
	//	{
	//		_listCollisionObject.push_back(_listNearByObject->at(value%100).at(value/100));
	//	}
	//}

	//for (int i = currentObjectRow; i < currentObjectRow + nearbyObjectCountHeight; i++)
	//{
	//	int value = (*_map)[i][currentObjectColumn - 1];
	//	if (value != -1)
	//	{
	//		_listCollisionObject.push_back(_listNearByObject->at(value % 100).at(value / 100));
	//	}
	//	value = (*_map)[i][currentObjectColumn + nearbyObjectCountWidth];
	//	if (value != -1)
	//	{
	//		_listCollisionObject.push_back(_listNearByObject->at(value % 100).at(value / 100));
	//	}
	//}

}
void DynamicObject::Update()
{
	_listCollisionObject.clear();
}

void DynamicObject::InitMapData(int*** map, int row, int column, Object** listStaticObject)
{
	_map = map;
	_row = row;
	_column = column;
	*_listStaticObject = listStaticObject;
}
DynamicObject::~DynamicObject()
{
	//for (int i = 0; i < NUM_OF_DIRECTION; i++)
///	{
	//	delete this->_listSprite[i];
	//}
	//delete this->_listSprite;
}
