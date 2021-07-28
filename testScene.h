#pragma once
#include "gameNode.h"
#include "TileClass.h"
class testScene : public gameNode
{
private:
	TileClass * _tileClass;
	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

