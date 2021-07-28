#include "stdafx.h"
#include "testScene.h"

HRESULT testScene::init()
{
	_tileClass = new TileClass;
	_tileClass->init("tile_Home.map");

	return S_OK;
}

void testScene::release()
{

}

void testScene::update()
{
	_tileClass->update();
}

void testScene::render()
{
	_tileClass->render();
}
