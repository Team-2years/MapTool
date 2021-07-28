#pragma once
#include <vector>
#include "gameNode.h"
#include "D_Object.h"

class ObjectManger : public gameNode
{
private:
	typedef vector<D_Object*>				vObject;
	typedef vector<D_Object*>::iterator		viObject;

private:

	vObject _vObject;
	viObject _viObject;



public:
	ObjectManger() {};
	~ObjectManger() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setObject(const char* name, float x, float y);

	void collision();

	void removeObject(int arrNum);

	vector<D_Object*> getvObject() { return _vObject; }
	vector<D_Object*>::iterator getviObject() { return _viObject; }
};