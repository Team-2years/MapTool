#include "stdafx.h"
#include "ObjectManger.h"

HRESULT ObjectManger::init()
{
	return S_OK;
}

void ObjectManger::release()
{
}

void ObjectManger::update()
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		(*_viObject)->update();
		(*_viObject)->move();
	}
}

void ObjectManger::render()
{
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		(*_viObject)->render();

	}
}

void ObjectManger::setObject(const char* name, float x, float y)
{
	D_Object* Jar;
	Jar = new D_Object;
	Jar->init(name, PointMake(x, y));

	_vObject.push_back(Jar);

}

void ObjectManger::collision()
{
	//RECT temp;
	//RECT rc = RectMake(_pl->getRCplayer()->left, _pl->getRCplayer()->top, _pl->getRCplayer()->right - _pl->getRCplayer()->left, _pl->getRCplayer()->bottom - _pl->getRCplayer()->top);
	//RECT rc2 = RectMake(_pl->getRCplayerAteeck()->left, _pl->getRCplayerAteeck()->top,
	//	_pl->getRCplayerAteeck()->right - _pl->getRCplayerAteeck()->left, _pl->getRCplayerAteeck()->bottom - _pl->getRCplayerAteeck()->top);
	//for (_viEyefly = _vEyefly.begin(); _viEyefly != _vEyefly.end(); ++_viEyefly)
	//{
	//	RECT rc5 = (*_viEyefly)->getRect();
	//	if (IntersectRect(&temp, &rc5, &rc))
	//	{

	//		_pl->lifeDamge(1);
	//		_pl->death();
	//		_pl->deathSwith();
	//	}


	//}


}

void ObjectManger::removeObject(int arrNum)
{
	_vObject.erase(_vObject.begin() + arrNum);
}
