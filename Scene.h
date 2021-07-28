#pragma once
#include "gameNode.h"
#include <vector>

//class Player;

class Scene : public gameNode
{
protected:
	//static Player* _player;

public:
	Scene() {};
	~Scene() {};

	virtual HRESULT init();
	//virtual HRESULT init(Player* player);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void changeScene() = 0;
};