#include "GDI-Capture.h"


const int width = 640;
const int height = 640;

int main(int argc, char* argv[])
{
	GDI_Capture cap(width, height);

	double fps = 0.f;
	double start = 0.f, end = 0.f;
	double totalFrames = 0.f;
	double elapsedTime = 0.f;

	for (;;)
	{
		start = cv::getTickCount();
		cv::Mat img = cap.CapCenter();

		end = cv::getTickCount();
		totalFrames++;
		elapsedTime += (end - start) / cv::getTickFrequency();

		if (elapsedTime > 1.0) { // 每隔一秒钟计算一次fps
			fps = totalFrames / elapsedTime;

			// 重置计数器
			totalFrames = 0;
			elapsedTime = 0;
		}
		cv::putText(img, "FPS: " + std::to_string(fps), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
		
		cv::imshow("test", img);
		cv::waitKey(1);
	}
	
	return 0;
}