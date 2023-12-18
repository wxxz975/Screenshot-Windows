#include "DirectX-Capture.h"

#include <opencv2/opencv.hpp>

/* 
	���ַ�ʽ��Ҫ�������ϵĽ�ȡͼƬ
	��Ϊ�������õ�AcquireNextFrame����ȴ�ʱ��Ϊ0��������Ȼ������������û��ȡ�����ݣ���ʵ�Ⲣ����������Ч�ʸ�
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

		if (elapsedTime > 1.0) { // ÿ��һ���Ӽ���һ��fps
			fps = totalFrames / elapsedTime;

			// ���ü�����
			totalFrames = 0;
			elapsedTime = 0;
		}
		cv::putText(img, "FPS: " + std::to_string(fps), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);


		cv::imshow("test", img);
		cv::waitKey(100);
	}
	

	return 0;
}