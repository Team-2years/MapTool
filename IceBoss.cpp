#include "stdafx.h"
#include "IceBoss.h"

HRESULT IceBoss::init()
{
	_tileClass = new TileClass;
	_tileClass->init("tile_IceBoss.map");
	//_tileClass->setBossDungeon("tile_Ice.map");
	return S_OK;
}

void IceBoss::release()
{
}

void IceBoss::update()
{
	_tileClass->update();
}

void IceBoss::render()
{
	_tileClass->render();
}
