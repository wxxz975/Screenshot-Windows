#pragma once
#include <vector>
#include <string>
#include <d3d11.h>
#include <dxgi1_2.h>

#include "../Shared/Capturer.h"

typedef std::string Error;

// BGRA U8 Bitmap
struct Bitmap {
	int                  Width = 0;
	int                  Height = 0;
	std::vector<uint8_t> Buf;
};

// WinDesktopDup hides the gory details of capturing the screen using the
// Windows Desktop Duplication API
class WinDesktopDup {
public:
	Bitmap Latest;
	int    OutputNumber = 0;

	~WinDesktopDup();

	Error Initialize();
	void  Close();
	bool  CaptureNext(const RECT& rect);

private:
	void CheckBitmapShape(int width, int height);

private:
	ID3D11Device*			D3DDevice			= nullptr;
	ID3D11DeviceContext*	D3DDeviceContext	= nullptr;
	IDXGIOutputDuplication* DeskDupl			= nullptr;
	DXGI_OUTPUT_DESC        OutputDesc;
	bool                    HaveFrameLock		= false;
};


class DirectX_Capture : public Capturer
{
public:
	DirectX_Capture(int width, int height);
	~DirectX_Capture();


	const cv::Mat& CapCenter() override;

private:
	WinDesktopDup dumper;

	cv::Mat img;
};