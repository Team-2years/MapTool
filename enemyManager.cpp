#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{
	IMAGEMANAGER->addFrameImage("plant_bullet", L"bullet_img/plant_bullet.png", 168, 18, 6, 1);

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{
		(*_pool_iter)->update();
	}
}

void enemyManager::render()
{
	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{
		(*_pool_iter)->render();
	}
}

POINT enemyManager::PointMake(int x, int y)
{
	POINT temp;

	temp.x = x;
	temp.y = y;

	return temp;
}
