#pragma once

#include <Windows.h>
#include <dwrite.h>
#include <d2d1.h>
#include <string>
#include "Resource.h"


class Graphics
{
	ID2D1Factory* factory;
	IDWriteFactory* DWriteFactory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

	IDWriteTextFormat* textFormat32;
	IDWriteTextFormat* textFormat64;
	IDWriteTextFormat* textFormat128;

public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);
	bool InitText(float textSize);
	float fontSize = NULL;


	ID2D1RenderTarget* GetRenderTarget()
	{
		return renderTarget;
	}

	void BeginDraw() 
	{
		renderTarget->BeginDraw();
	}
	void EndDraw() 
	{
		renderTarget->EndDraw();
	}

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void FillCircle(float x, float y, float radius, float r, float g, float b, float a);
	void FillRect(float x, float y, float length, float width, float r, float g, float b, float a);
	void renderCharacters(float x, float y, float r, float g, float b, float a, std::wstring textArg, unsigned int mode);

};