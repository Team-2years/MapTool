#include "stdafx.h"
#include "dtdManager.h"

HRESULT dtdManager::init()
{
	_dFactory = nullptr;
	_dRenderTarget = nullptr;
	_dBitRenderTarget = nullptr;
	_dBitmap = nullptr;
	_dBrush = nullptr;

	_dWFactory = nullptr;
	_dWFormat = nullptr;

	_clear = true;

	HRESULT hr;

	//Fafctory 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_dFactory);

	//Factory가 생성되었으면 RenderTarget 생성
	if (SUCCEEDED(hr)) {
		hr = _dFactory->CreateHwndRenderTarget(RenderTargetProperties(),
			HwndRenderTargetProperties(_hWnd, SizeU(WINSIZEX, WINSIZEY)),
			&_dRenderTarget);
	}

	////RenderTarget과 호환되는 또 다른 RenderTarget(=BackBuffer) 생성
	//if (SUCCEEDED(hr)) {
	//	hr = _dRenderTarget->CreateCompatibleRenderTarget(SizeF(WINSIZEX * 2, WINSIZEY * 2),
	//		SizeU(WINSIZEX * 2, WINSIZEY * 2),
	//		&_dBitRenderTarget
	//	);
	//}

	//RenderTarget이 생성되었으면 Brush 생성
	if (SUCCEEDED(hr)) {
		hr = _dRenderTarget->CreateSolidColorBrush(ColorF(ColorF::Black), &_dBrush);
	}

	//Brush가 생성되었으면 Text Factory 생성
	if (SUCCEEDED(hr)) {
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&_dWFactory)
		);
	}

	//Text Factory가 생성되었으면 Text Format 생성
	if (SUCCEEDED(hr)) {
		hr = _dWFactory->CreateTextFormat(
			L"돋움",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30.0f,
			L"ko-kr",
			&_dWFormat
		);
	}

	//Text Format이 생성되었으면 기본값(가운데 정렬) 설정
	/*if (SUCCEEDED(hr)) {
		hr = _dWFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		if (SUCCEEDED(hr)) {
			hr = _dWFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		}
	}*/

	//wincodec(이미지 로더)을 사용하기 위함
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	return S_OK;
}

void dtdManager::release()
{
	//동적 할당한 객체들 모두 해제
	SAFE_RELEASE2(_dFactory);
	SAFE_RELEASE2(_dRenderTarget);
	SAFE_RELEASE2(_dBrush);
	SAFE_RELEASE2(_dWFactory);
	SAFE_RELEASE2(_dWFormat);
}

void dtdManager::render()
{
	if (!_dRenderTarget) return;

	_dRenderTarget->BeginDraw();
	_dRenderTarget->Clear(ColorF(ColorF::White));

	/*SAFE_RELEASE2(_dBitmapBrush);
	_dRenderTarget->CreateBitmapBrush(_dBitmap,
		BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP),
		&_dBitmapBrush);
	D2D1_RECT_F rc = dRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	_dRenderTarget->FillRectangle(rc, _dBitmapBrush);*/

	RECT screen = CAMERAMANAGER->getScreen();
	D2D1_RECT_F dest = { 0, 0, WINSIZEX, WINSIZEY };
	D2D1_RECT_F sour = { screen.left, screen.top, screen.right, screen.bottom };

	if (_dRenderTarget) {
		_dRenderTarget->DrawBitmap(_dBitmap, dest,
			1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sour);
	}

	_dRenderTarget->EndDraw();
}

void dtdManager::render(RECT rc)
{
	_dRenderTarget->BeginDraw();
	_dRenderTarget->Clear(ColorF(ColorF::White));

	//_dRenderTarget->DrawRectangle(rc);

	_dRenderTarget->EndDraw();
}

void dtdManager::beginDraw()
{
	if (_dBitRenderTarget) {
		_dBitRenderTarget->BeginDraw();
		_dBitRenderTarget->Clear();
	}
}

void dtdManager::endDraw()
{
	if (_dBitRenderTarget) {
		//SAFE_RELEASE2(_dBitmap);
		_dBitRenderTarget->GetBitmap(&_dBitmap);

		_dBitRenderTarget->EndDraw();
	}
}

void dtdManager::Rectangle(D2D1_RECT_F rc)
{
	if (_dBitRenderTarget)
		_dBitRenderTarget->DrawRectangle(rc, _dBrush);
}

void dtdManager::Rectangle(RECT rc)
{
	D2D1_RECT_F d2dRC = { rc.left, rc.top, rc.right, rc.bottom };
	D2D1_POINT_2F pt = { (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 };



	if (_dBitRenderTarget)
		_dBitRenderTarget->DrawRectangle(d2dRC, _dBrush);
	//_dBitRenderTarget->FillRectangle(d2dRC, _dBrush);


}
void dtdManager::Rectangle(RECT rc , float angle)
{
	D2D1_RECT_F d2dRC = { rc.left, rc.top, rc.right, rc.bottom };



	if (_dBitRenderTarget)
		_dBitRenderTarget->DrawRectangle(d2dRC, _dBrush);


}

void dtdManager::printText(LPCWCHAR text, float x, float y, float width, float height)
{
	_dBitRenderTarget->DrawTextA(text, lstrlenW(text), _dWFormat, dRectMakeCenter(x, y, width, height), _dBrush);
}

void dtdManager::printText(LPCWCHAR text, D2D1_RECT_F rc)
{
	_dBitRenderTarget->DrawTextA(text, lstrlenW(text), _dWFormat, rc, _dBrush);
}

void dtdManager::setBackBuffer(float width, float height)
{
	SAFE_RELEASE2(_dBitRenderTarget);

	if (_dRenderTarget) {
		_dRenderTarget->CreateCompatibleRenderTarget(SizeF(width, height), &_dBitRenderTarget);
	}
}

void dtdManager::setRotation(float angle, float x, float y)
{
	D2D1_POINT_2F pt = { x, y };
	_dBitRenderTarget->SetTransform(Matrix3x2F::Rotation(angle, pt));
}

void dtdManager::resetRotation()
{
	_dBitRenderTarget->SetTransform(Matrix3x2F::Identity());
}

void dtdManager::resetWindowSize(UINT width, UINT height)
{

	if (_dRenderTarget)
	{
		D2D1_SIZE_U size;
		size.width = width;
		size.height = height;
		_dRenderTarget->Resize(size);

		WinsizeX = size.width;
		WinsizeY = size.height;

	}
}
