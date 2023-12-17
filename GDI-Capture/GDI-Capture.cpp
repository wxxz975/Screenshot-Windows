#include "GDI-Capture.h"




GDI_Capture::GDI_Capture(int width, int height, HWND screen_id)
	:Capturer(width, height)
{
	hScreenDC = GetDC(screen_id);
	
	hMemoryDC = CreateCompatibleDC(hScreenDC);
	hBitmap = CreateCompatibleBitmap(hScreenDC, capture_width_, capture_height_);
	SelectObject(hMemoryDC, hBitmap);


	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = capture_width_;
	bi.biHeight = -capture_height_;  // negative height to ensure a top-down DIB
	bi.biPlanes = 1;
	bi.biBitCount = 24;  // assuming 24 bits per pixel (adjust if necessary)
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;  // can be set to 0 for BI_RGB compression
}

const cv::Mat& GDI_Capture::CapCenter()
{
	BitBlt(hMemoryDC, 0, 0, capture_width_, capture_height_, hScreenDC, capture_x_, capture_y_, SRCCOPY);
	
	// 获取截图数据
	GetDIBits(hMemoryDC, hBitmap, 0, capture_height_, img.data, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS);
	
	return img;
}
