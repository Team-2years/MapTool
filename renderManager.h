#pragma once
#include "singletonBase.h"



struct tagUnit
{
	// image
	dImage* img;
	// 그려줄 위치
	float x, y;
	// 그려줄 사이즈
	float sizeWidth, sizeHeight;
	// 프레임 x, y
	int frameX, frameY;
	// frame?
	bool isFrame;
	// blend val
	float alpha;
};
class renderManager : public singletonBase<renderManager>
{
private:
	typedef vector<pair<float, tagUnit>> _zOrder_vector;
	typedef vector<pair<float, tagUnit>>::iterator _zOrder_vector_iter;
private:
	_zOrder_vector _zOrder;
	vector<dImage> _noneZOrder;
	float _cameraX;
	float _cameraY;
public:
	renderManager();
	~renderManager();

	HRESULT init();
	void release();
	void render();

	void push_BackRenderInfo(float zOrder_Bottom, dImage* img, float x, float y, float alpha = 1.f);
	void push_BackRenderInfo(float zOrder_Bottom, dImage* img, float x, float y, float sizeWidth, float sizeHeight, float alpha = 1.f);
	void push_BackFrameRenderInfo(float zOrder_Bottom, dImage* img, float x, float y, float _alpha = 1.f);
	void push_BackFrameRenderInfo(float zOrder_Bottom, dImage* img, float x, float y, int currentFrameX, int currentFrameY, float _alpha = 1.f);
	void push_BackFrameRenderInfo(float zOrder_Bottom, dImage* img, float x, float y, int currentFrameX, int currentFrameY, float sizeWidth, float sizeHeight, float _alpha = 1.f);
	void mergeSort(vector<pair<float, tagUnit>>& v, int s, int e);
	void merge(vector<pair<float, tagUnit>>& v, int s, int e, int m);
};

