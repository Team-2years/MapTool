#include "stdafx.h"
#include "LineVariation.h"

HRESULT LineVariation::init()
{
	_tileClass = new TileClass;
	/*int temp = RND->getInt(2);
	switch (temp)
	{
	case 0:
		_tileClass->init("tile_IceRoad1.map");
		break;
	case 1:
		_tileClass->init("tile_IceRoad2.map");
		break;
	default:
		break;
	}
	_tileClass->setRandomDungeon("tile_Ice.map");*/
	_tileClass->init("tile_IceRoad1.map");
	return S_OK;
}

void LineVariation::release()
{
}

void LineVariation::update()
{
	_tileClass->update();
}

void LineVariation::render()
{
	_tileClass->render();
}
