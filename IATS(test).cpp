#include<opencv2/opencv.hpp>
#include"image.h"
int main() {
	cv::Mat img = cv::Mat(cv::Size(32, 32), CV_8UC4, image_virnect);

	cv::imshow("test", img);
	cv::waitKey();
	cv::destroyAllWindows();
	return 0;
}