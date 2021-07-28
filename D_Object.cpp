#include "stdafx.h"
#include "D_Object.h"

HRESULT D_Object::init()
{
	return S_OK;
}

HRESULT D_Object::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_count = 0;



	_imageName = IMAGEMANAGER->findDImage(imageName);

	_rc = RectMakeCenter(position.x, position.y,
		_imageName->getFrameWidth(), _imageName->getFrameHeight());

	_x = position.x;
	_y = position.y;
	return S_OK;
}

void D_Object::release()
{
}

void D_Object::update()
{
	_count++;
	if (_count % 5 == 0)
	{
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;

		_count = 0;
	}

}

void D_Object::render()
{
	draw();
}

void D_Object::move()
{
}

void D_Object::draw()
{
	_imageName->frameRender( _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}
