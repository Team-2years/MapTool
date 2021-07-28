#include "stdafx.h"
#include "iceScene.h"

HRESULT IceScene::init()
{
	_tileClass = new TileClass;
	_tileClass->init("tile_Ice.map");

	return S_OK;
}

void IceScene::release()
{

}

void IceScene::update()
{
	_tileClass->update();
}

void IceScene::render()
{
	_tileClass->render();
}
