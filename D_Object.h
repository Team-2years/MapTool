#pragma once
#include "gameNode.h"

class D_Object : public gameNode
{
protected:
	dImage* _imageName;		//���ʹ� �̹���
	RECT _rc;				//��Ʈ
	float _x, _y;
	int _currentFrameX;		//�����ӹ�ȣ�� ����� ����
	int _currentFrameY;

	int _count;				//�����ӷ����� ��


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