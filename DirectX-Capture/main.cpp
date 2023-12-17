#include "DirectX-Capture.h"

#include <opencv2/opencv.hpp>

int main(int argc, char* argv[])
{

	WinDesktopDup dumper;
	
	auto initRet = dumper.Initialize();
	std::cout << "init ret:" << initRet.c_str() << "\n";
	if (initRet.empty()) {

		double fps = 0.f;
		double start = 0.f, end = 0.f;
		double totalFrames = 0.f;
		double elapsedTime = 0.f;

		int cnt = 1000;
		while (cnt--)
		{
			start = cv::getTickCount();

			dumper.CaptureNext();
			Bitmap bitmap = dumper.Latest;

			cv::Mat img = cv::Mat(bitmap.Height, bitmap.Width, CV_8UC4, bitmap.Buf.data());

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
			cv::waitKey(100);
		}
	}

	dumper.Close();

	return 0;
}