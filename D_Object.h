#pragma once
#include "gameNode.h"

class D_Object : public gameNode
{
protected:
	dImage* _imageName;		//에너미 이미지
	RECT _rc;				//렉트
	float _x, _y;
	int _currentFrameX;		//프레임번호로 사용할 변수
	int _currentFrameY;

	int _count;				//프레임렌더링 용


public:
	D_Object() {};
	~D_Object() {};

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void draw();




};