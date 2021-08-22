#pragma once
#include <memory>
#include "Win32Window.h"

class ScreenBuffer
{
	friend class Renderer;

public:
	ScreenBuffer(std::shared_ptr<Window>& window, int width, int height);
	~ScreenBuffer();

	void setViewport(int width, int height);
	void Clear(float r, float g, float b);
	void ClearDepthBuffer();

	void* getBuffer() { return m_MemoryBuffer; }
	int getWidth() { return m_Width; }
	int getHeight() { return m_Height; }

	void Render();

private:
	void* m_MemoryBuffer = nullptr;
	float* m_DepthBuffer = nullptr;

	BITMAPINFO m_BitMapInfo;

	std::shared_ptr<Window> m_Window;
	uint32 m_BufferSize;

	int m_Width;
	int m_Height;
};