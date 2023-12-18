#include "DirectX-Capture.h"

#include <opencv2/opencv.hpp>

/* 
	这种方式需要持续不断的截取图片
	因为我们设置的AcquireNextFrame这个等待时间为0，所以虽然返回了他可能没获取到数据，其实这并不代表他的效率高
*/
int main(int argc, char* argv[])
{

	DirectX_Capture cap(640, 640);
	
	double fps = 0.f;
	double start = 0.f, end = 0.f;
	double totalFrames = 0.f;
	double elapsedTime = 0.f;

	int cnt = 1000;
	while (true)
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
		cv::waitKey(100);
	}
	

	return 0;
}