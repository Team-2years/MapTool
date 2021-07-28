#include "stdafx.h"
#include "villageScene.h"

HRESULT villageScene::init()
{
	_tileClass = new TileClass;
	_tileClass->init("tile_Village.map");
	return S_OK;
}

void villageScene::release()
{
}

void villageScene::update()
{
	_tileClass->update();
}

void villageScene::render()
{
	_tileClass->render();
}
