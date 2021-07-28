#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = 0;

	_Fire_interval = RND->getFromIntTo(1, 500);

	enemy_img = IMAGEMANAGER->findImage(imageName);

	_rc = D2DMANAGER->RectMakeCenter(position.x, position.y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_direction = 0;

	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position, int direction)
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	move();
	KEYANIMANAGER->update();
}

void enemy::render()
{
	draw();
}

void enemy::move()
{
}

bool enemy::bullet_Fire()
{
	if (_fireCount % _Fire_interval == 0)
	{
		_Fire_interval = 135;
		_fireCount = 0;
		//is_set = true;
	}
	
	return true;
}

void enemy::draw()
{

}
