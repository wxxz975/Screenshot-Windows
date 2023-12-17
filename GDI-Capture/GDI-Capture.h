#pragma once
#include "../Shared/Capturer.h"


class GDI_Capture : public Capturer
{
public:
	explicit GDI_Capture(int width, int height, HWND screen_id = 0);
	~GDI_Capture() = default;

	const cv::Mat& CapCenter() override;


private:
	HDC hScreenDC;
	HDC hMemoryDC;

	HBITMAP hBitmap;

	BITMAPINFOHEADER bi = {0};
};