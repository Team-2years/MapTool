#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* enemy_img;		//���ʹ� �̹���
	animation* enemy_body;

	D2D1_RECT_F _rc;

	int _currentFrameX;		//�����ӹ�ȣ�� ����� ����
	int _currentFrameY;

	int _count;				//�����ӷ����� ��

	int _fireCount;			//�߻� ī��Ʈ ��
	int _Fire_interval;			//�߻� �ֱ�

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

