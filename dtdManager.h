#pragma once
#include "singletonBase.h"

class dtdManager : public singletonBase<dtdManager>
{
private:
	//Factory, RenderTarget
	ID2D1Factory			*_dFactory;
	ID2D1HwndRenderTarget	*_dRenderTarget;
	ID2D1BitmapRenderTarget	*_dBitRenderTarget;
	ID2D1Bitmap				*_dBitmap;

	//Brush
	ID2D1BitmapBrush		*_dBitmapBrush;
	ID2D1SolidColorBrush	*_dBrush;

	//Text
	IDWriteFactory			*_dWFactory;
	IDWriteTextFormat		*_dWFormat;

	//Camera

	float _sizeX;
	float _sizeY;

	bool _clear;

public:
	HRESULT init();
	void release();
	void render();
	void render(RECT rc);

	void beginDraw();
	void endDraw();

	void Rectangle(D2D1_RECT_F rc);
	void Rectangle(RECT rc);
	void Rectangle(RECT rc , float angle);
	void printText(LPCWCHAR text, float x, float y, float width, float height);
	void printText(LPCWCHAR text, D2D1_RECT_F rc);

	void setBackBuffer(float width, float height);

	void setRotation(float angle, float x, float y);

	void resetRotation();

	void sizeUP() { _sizeX += 0.01; _sizeY += 0.01; }
	void sizeDOWN() { _sizeX -= 0.01; _sizeY -= 0.01; }
	void resetSize() { _sizeX = 1.0; _sizeY = 1.0; }
	void resetWindowSize(UINT width, UINT height);

	D2D1_COLOR_F getBrushColor() { return _dBrush->GetColor(); }
	void setBrushColor(D2D1_COLOR_F color) { _dBrush->SetColor(color); }

	ID2D1HwndRenderTarget* getRenderTarget() { return _dRenderTarget; }
	ID2D1BitmapRenderTarget* getBitRenderTarget() { return _dBitRenderTarget; }

	void setClear(bool clear) { _clear = clear; }
	bool getClear() { return _clear; }
};

