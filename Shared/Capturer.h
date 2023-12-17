#pragma once

#include <Windows.h>
#include <opencv2/opencv.hpp>

class Capturer
{
public:
	explicit Capturer(int capture_width = 640, int capture_height = 640);
	~Capturer() = default;


	virtual const cv::Mat& CapCenter() = 0;

protected:
	int screen_width_;
	int screen_height_;

	int capture_width_;
	int capture_height_;

	int capture_x_;
	int capture_y_;

	cv::Mat img;
};


inline Capturer::Capturer(int capture_width, int capture_height)
	:capture_width_(capture_width), capture_height_(capture_height)
{
	//hScreenDC = GetDC(screen_num);

	screen_width_ = GetSystemMetrics(SM_CXSCREEN);
	screen_height_ = GetSystemMetrics(SM_CYSCREEN);

	assert(capture_width_ < screen_width_ && capture_height_ << screen_height_);
	
	// 计算截图区域的左上角坐标
	capture_x_ = (screen_width_ - capture_width_) / 2;
	capture_y_ = (screen_height_ - capture_height_) / 2;

	img = cv::Mat(capture_width_, capture_height_, CV_8UC3);
	
	std::cout << "screen width:" << screen_width_ << " screen height:" << screen_height_
		<< " capture x:" << capture_x_ << " capture y:" << capture_y_ << "\n";

}