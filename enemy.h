#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* enemy_img;		//에너미 이미지
	animation* enemy_body;

	D2D1_RECT_F _rc;

	int _currentFrameX;		//프레임번호로 사용할 변수
	int _currentFrameY;

	int _count;				//프레임렌더링 용

	int _fireCount;			//발사 카운트 용
	int _Fire_interval;			//발사 주기

	int _direction;

	float _width;
	float _height;

	float _speed;
	float _angle;

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init(const char* imageName, POINT position, int direction);

	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();
	virtual bool bullet_Fire();

	void draw();

};

