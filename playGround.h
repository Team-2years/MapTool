#pragma once
#include "gameNode.h"

class playGround : public gameNode
{
private:
	bool _debug;

public:
	playGround();
	~playGround();
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};